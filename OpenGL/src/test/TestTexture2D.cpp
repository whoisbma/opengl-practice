#include "TestTexture2D.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>

using namespace test;

TestTexture2D::TestTexture2D(const std::string& name)
:	Test(name),
	m_translationA(200, 200, 0),
	m_translationB(400, 200, 0),
	m_proj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)),
	m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{

	float positions[] = {
		-75.0f, -60.0f, 0.0f, 0.0f,
		 75.0f, -60.0f, 1.0f, 0.0f,
		 75.0f,  60.0f, 1.0f, 1.0f,
		-75.0f,  60.0f, 0.0f, 1.0f
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
	layout.push<float>(2);
	layout.push<float>(2);	//  add texture coords
	
	m_VAO->addBuffer(*m_vertexBuffer, layout);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	m_shader->bind();

	m_texture = std::make_unique<Texture>("res/textures/doge.jpg");
	m_shader->setUniform1i("u_texture", 0);

	std::cout << "created test for " << name << std::endl;
}

TestTexture2D::~TestTexture2D()
{
}

void TestTexture2D::onUpdate(float deltatime)
{

}

void TestTexture2D::onRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;

	m_texture->bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void TestTexture2D::onImGuiRender()
{
	ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.0f, 640.0f);
	ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.0f, 640.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

