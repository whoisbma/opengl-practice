#include "TestMatrixOps.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>

using namespace test;

// TODO - matrix values controllable in imgui

TestMatrixOps::TestMatrixOps(const std::string & name)
	: Test(name),
	m_translation(0, 0, 0),
	m_proj(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 1.0f, 10.0f)),
	m_view(glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f), // position of the camera
		glm::vec3(0.0f, 0.0f, 0.0f), // point to be centered on-screen
		glm::vec3(0.0f, 1.0f, 0.0f)  // the up axis
	))
{
	float positions[] = {
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_VAO = std::make_unique<VertexArray>();
	VertexArray va;
	m_vertexBuffer = std::make_unique<VertexBuffer>(positions, 5 * 3 * sizeof(float));

	VertexBufferLayout layout;
	layout.push<float>(2); // x and y
	layout.push<float>(3); // rgb

	m_VAO->addBuffer(*m_vertexBuffer, layout);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 3);
	m_shader = std::make_unique<Shader>("res/shaders/vertexColor.shader");
	m_shader->bind();
	std::cout << "created test for " << name << std::endl; 
}

void TestMatrixOps::onUpdate(double deltaTime) {
	m_time = (float)deltaTime;
}

void TestMatrixOps::onRender()
{
	Renderer renderer;
	renderer.clear();
	{
		// try a simple rotation
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(m_time * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 model = glm::translate(trans, m_translation);
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		m_shader->setUniform1f("u_time", m_time);
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void TestMatrixOps::onImGuiRender()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
