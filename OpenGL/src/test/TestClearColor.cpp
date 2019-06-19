#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include <iostream>
#include <string>

using namespace test;

TestClearColor::TestClearColor(const std::string& name)
: 
	m_clearColor{ 0.2f, 0.3f, 0.8f, 1.0f },
	Test(name)
{
	std::cout << "created test for " << name << std::endl;
}

TestClearColor::~TestClearColor()
{
}

void TestClearColor::onUpdate(double deltatime)
{

}

void TestClearColor::onRender()
{
	GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::onImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", m_clearColor);
}

