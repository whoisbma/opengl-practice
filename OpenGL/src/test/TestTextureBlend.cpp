#include "TestTextureBlend.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>

using namespace test;

TestTextureBlend::TestTextureBlend(const std::string& name) :
	Test(name),
	m_translationA(320, 240, 0),
	m_proj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)),
	m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_blendAmt(0.5f)
{

	float positions[] = {
		-200.0f, -200.0f, 0.0f, 0.0f,
		 200.0f, -200.0f, 1.0f, 0.0f,
		 200.0f,  200.0f, 1.0f, 1.0f,
		-200.0f,  200.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_VAO = std::make_unique<VertexArray>();

	VertexArray va;
	m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float)); // 4 floats per vertex

	VertexBufferLayout layout;
	layout.push<float>(2);  //  add x and y 
	layout.push<float>(2);	//  add texture coords

	m_VAO->addBuffer(*m_vertexBuffer, layout);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_shader = std::make_unique<Shader>("res/shaders/blendedTextures.shader");
	m_shader->bind();

	m_textureA = std::make_unique<Texture>("res/textures/kitten.png");
	m_textureB = std::make_unique<Texture>("res/textures/puppy.jpg");
	m_shader->setUniform1i("u_textureA", 0);
	m_shader->setUniform1i("u_textureB", 1);
	m_shader->setUniform1f("u_blendAmt", m_blendAmt);

	std::cout << "created test for " << name << std::endl;
}

void TestTextureBlend::onUpdate(double deltatime)
{

}

void TestTextureBlend::onRender()
{
	Renderer renderer;
	renderer.clear();

	m_textureA->bind(0);
	m_textureB->bind(1);
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		m_shader->setUniform1f("u_blendAmt", m_blendAmt);
		// renderer gets the vertex array object (the vertex model plus the actual vertex data) the index buffer, and the shader
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void TestTextureBlend::onImGuiRender()
{
	//ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 640.0f);
	ImGui::SliderFloat("Blend Amount", &m_blendAmt, 0.0f, 1.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

