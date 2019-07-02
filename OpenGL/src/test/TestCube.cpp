#include "TestCube.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>

using namespace test;

TestCube::TestCube(const std::string & name) :
	Test(name),
	m_fov(45.0f),
	m_translation(0, 0, 0),
	m_camera(0.0f, 0.0f, 3.0f),
	m_target(0.0f, 0.0f, 0.0f),
	m_upAxis(0.0f, 1.0f, 0.0f),
	m_blendAmt(0.5f)
{
	m_proj = glm::perspective(glm::radians(m_fov), 640.0f / 480.0f, 1.0f, 20.0f);
	m_view = glm::lookAt(m_camera, m_target, m_upAxis);

	float vertices[] = {
	  // X      Y     Z     R     G     B     U     V
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_VAO = std::make_unique<VertexArray>();
	VertexArray va;
	m_vertexBuffer = std::make_unique<VertexBuffer>(vertices, 24 * 8 * sizeof(float));

	VertexBufferLayout layout;
	layout.push<float>(3); // xyz
	layout.push<float>(3); // rgb
	layout.push<float>(2); // uv

	m_VAO->addBuffer(*m_vertexBuffer, layout);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices, 36);
	m_shader = std::make_unique<Shader>("res/shaders/cube.shader");
	m_shader->bind();

	m_textureA = std::make_unique<Texture>("res/textures/kitten.png");
	m_textureB = std::make_unique<Texture>("res/textures/puppy.jpg");
	m_shader->setUniform1i("u_textureA", 0);
	m_shader->setUniform1i("u_textureB", 1);
	m_shader->setUniform1f("u_blendAmt", m_blendAmt);

	std::cout << "created test for " << name << std::endl; 
}

void TestCube::onUpdate(double deltaTime) {
	m_time = (float)deltaTime;
}

void TestCube::onRender()
{
	Renderer renderer;
	renderer.clear();

	m_textureA->bind(0);
	m_textureB->bind(1);
	{
		glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, glm::radians(m_time * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 model = glm::translate(trans, m_translation);
		model = glm::rotate(model, glm::radians(m_time * 30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		m_shader->setUniform1f("u_blendAmt", m_blendAmt);
		m_shader->setUniform1f("u_time", m_time);
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void TestCube::onImGuiRender()
{
	ImGui::SliderFloat3("Translation", glm::value_ptr(m_translation), -10.0f, 10.0f);

	if (ImGui::SliderFloat3("Camera Position", glm::value_ptr(m_camera), -5.0f, 5.0f)) {
		m_view = glm::lookAt(m_camera, m_target, m_upAxis);
	}

	if (ImGui::SliderFloat3("Camera Target", glm::value_ptr(m_target), -5.0f, 5.0f)) {
		m_view = glm::lookAt(m_camera, m_target, m_upAxis);
	}

	if (ImGui::SliderFloat("Camera FOV", &m_fov, 0.0f, 100.0f)) {
		m_proj = glm::perspective(glm::radians(m_fov), 640.0f / 480.0f, 1.0f, 20.0f);
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
