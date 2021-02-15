#include "TestMatrixOps.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>

using namespace test;

TestMatrixOps::TestMatrixOps(const std::string & name) :
	Test(name),
	m_fov(45.0f),
	m_zoomfactor(1.0f),
	m_aspectratio(640.0f / 480.f),
	m_aspectcondition(16.0f / 9.0f),
	m_aspectratiox(1.0f),
	m_aspectratioy(1.0f),
	m_translation(0, 0, 0),
	m_camera(0.0f, 0.0f, 3.0f),
	m_target(0.0f, 0.0f, 0.0f),
	m_upAxis(0.0f, 1.0f, 0.0f)
{
	if (m_aspect > m_aspectcondition)
	{
		m_aspectratiox = m_aspectcondition / m_aspectratio;
	}
	
	m_proj = glm::perspective(2 * atan(tan(glm::radians(m_fov) / 2) / m_aspectratio * m_aspectcondition / m_aspectratiox / m_zoomfactor / m_aspectratioy), m_aspectratio * m_aspectratioy, 1.0f, 20.0f);
	m_view = glm::lookAt(m_camera, m_target, m_upAxis);

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
		glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, glm::radians(m_time * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 model = glm::translate(trans, m_translation);
		model = glm::rotate(model, glm::radians(m_time * 30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 mvp = m_proj * m_view * model;
		m_shader->bind();
		m_shader->setUniformMat4f("u_MVP", mvp);
		m_shader->setUniform1f("u_time", m_time);
		renderer.draw(*m_VAO, *m_indexBuffer, *m_shader);
	}
}

void TestMatrixOps::onImGuiRender()
{
	ImGui::SliderFloat3("Translation", glm::value_ptr(m_translation), -10.0f, 10.0f);

	if (ImGui::SliderFloat3("Camera Position", glm::value_ptr(m_camera), -5.0f, 5.0f)) {
		m_view = glm::lookAt(m_camera, m_target, m_upAxis);
	}

	if (ImGui::SliderFloat3("Camera Target", glm::value_ptr(m_target), -5.0f, 5.0f)) {
		m_view = glm::lookAt(m_camera, m_target, m_upAxis);
	}

	if (ImGui::SliderFloat("Camera FOV", &m_fov, 0.0f, 100.0f)) {
		if (m_aspect > m_aspectcondition)
		{
			m_aspectratiox = m_aspectcondition / m_aspectratio;
		}
		m_proj = glm::perspective(2 * atan(tan(glm::radians(m_fov) / 2) / m_aspectratio * m_aspectcondition / m_aspectratiox / m_zoomfactor / m_aspectratioy), m_aspectratio * m_aspectratioy, 1.0f, 20.0f);
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
