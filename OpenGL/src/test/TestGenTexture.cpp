#include "TestGenTexture.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>

using namespace test;

TestGenTexture::TestGenTexture(const std::string& name) :
	Test(name),
	m_translationA(320, 240, 0),
	m_scale(1.0f),
	m_proj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)),
	m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{

	float positions[] = {
		// coord			// texcoord		// color
		-235.0f, -200.0f,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 235.0f, -200.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		 235.0f,  200.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-235.0f,  200.0f,	0.0f, 1.0f,		1.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_VAO = std::make_unique<VertexArray>();

	VertexArray va;
	m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 7 * sizeof(float)); // 7 floats per vertex

	VertexBufferLayout layout;
	layout.push<float>(2);  //  add x and y 
	layout.push<float>(2);	//  add texture coords
	layout.push<float>(3);  //  add colors
	
	m_VAO->addBuffer(*m_vertexBuffer, layout);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_shader = std::make_unique<Shader>("res/shaders/generatedTexture.shader");
	m_shader->bind();

	m_texture = std::make_unique<Texture>();
	m_shader->setUniform1i("u_texture", 0);
	m_shader->setUniform1f("u_scale", m_scale);

	std::cout << "created test for " << name << std::endl;
}

void TestGenTexture::onUpdate(double deltatime)
{

}

void TestGenTexture::onRender()
{
	Renderer renderer;
	renderer.clear();

	m_texture->bind();
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		m_shader->setUniform1f("u_scale", m_scale);
		// renderer gets the vertex array object (the vertex model plus the actual vertex data) the index buffer, and the shader
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void TestGenTexture::onImGuiRender()
{
	ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 640.0f);
	ImGui::DragFloat("Scale", &m_scale, 0.1f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

