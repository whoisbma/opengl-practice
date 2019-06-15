#pragma once

#include "Test.h"

namespace test {
	class TestClearColor : Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_clearColor[4];
	};
}

