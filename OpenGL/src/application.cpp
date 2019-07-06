#include <GL/glew.h>
#include <GLFW/glfw3.h>	

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"
#include "test/TestVertexColor.h"
#include "test/TestGenTexture.h"
#include "test/TestTextureBlend.h"
#include "test/TestMatrixOps.h"
#include "test/TestCube.h"
#include "test/TestPlanarReflection.h"
#include "test/TestOutline.h"

void glfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "GLFW", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetErrorCallback(glfwErrorCallback);
	glfwSetKeyCallback(window, keyCallback);

	if (glewInit() != GLEW_OK) {
		std::cout << "glewInit() ERROR\n";
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_STENCIL_TEST));

		Renderer renderer;

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest, "Test Menu");
		currentTest = testMenu;

		testMenu->registerTest<test::TestClearColor>("Clear Color");
		testMenu->registerTest<test::TestTexture2D>("2D Texture");
		testMenu->registerTest<test::TestVertexColor>("Vertex Color");
		testMenu->registerTest<test::TestGenTexture>("Generate Texture");
		testMenu->registerTest<test::TestTextureBlend>("Blend Textures");
		testMenu->registerTest<test::TestMatrixOps>("Matrix Operations");
		testMenu->registerTest<test::TestCube>("Cube");
		testMenu->registerTest<test::TestPlanarReflection>("Planar Reflection");
		testMenu->registerTest<test::TestOutline>("Outline");

		while (!glfwWindowShouldClose(window)) {
			float ratio;
			int width, height;

			GLCall(glfwGetFramebufferSize(window, &width, &height));
			ratio = width / (float)height;
			GLCall(glViewport(0, 0, width, height));

			renderer.clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest) {
				currentTest->onUpdate(glfwGetTime());
				currentTest->onRender();
				ImGui::Begin(currentTest->getName().c_str());
				if (currentTest != testMenu && ImGui::Button("<--")) {
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->onImGuiRender();
				ImGui::End();
			}
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		delete currentTest;
		if (currentTest != testMenu) {
			delete testMenu;
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}