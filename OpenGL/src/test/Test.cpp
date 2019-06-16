#include "Test.h"
#include "imgui/imgui.h"

#include <string>
#include <iostream>

using namespace test;

TestMenu::TestMenu(Test*& currentTestPtr, const std::string& name)
	: m_currentTest(currentTestPtr), Test(name)
{
	std::cout << "created test for " << name << std::endl;
}

void TestMenu::onImGuiRender()
{
	for (auto& test : m_tests) {
		if (ImGui::Button(test.first.c_str())) {
			m_currentTest = test.second(test.first);
		}
	}
}
