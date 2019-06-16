#include "Test.h"
#include "imgui/imgui.h"

using namespace test;

TestMenu::TestMenu(Test*& currentTestPtr)
	: m_currentTest(currentTestPtr)
{
}

void TestMenu::onImGuiRender()
{
	for (auto& test : m_tests) {
		if (ImGui::Button(test.first.c_str())) {
			m_currentTest = test.second();
		}
	}
}
