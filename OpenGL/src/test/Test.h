#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <string>

namespace test {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(double deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}

		const std::string getName() const { return m_name; }

	protected:
		Test(const std::string& name) : m_name(name) { std::cout << "Base constructor called for " << name << std::endl; }
		std::string m_name;
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPtr, const std::string& name);

		void onImGuiRender() override;
		
		template<typename T>
		void registerTest(const std::string& name) {
			std::cout << "Registering test " << name << std::endl;
			m_tests.push_back(std::make_pair(name, [](const std::string& name) { 
				std::cout << "pushing back test for " << name << std::endl;
				return new T(name);
			}));
		}

	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test*(const std::string& name)>>> m_tests;
	};
}