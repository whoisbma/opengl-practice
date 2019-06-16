#pragma once

#include "Test.h"

namespace test {
	class TestClearColor : public Test
	{
	public:
		TestClearColor(const std::string& name);
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_clearColor[4];
	};
}

