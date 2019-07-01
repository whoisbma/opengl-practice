#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>
#include "glm/glm.hpp"

namespace test {
	class TestMatrixOps : public Test
	{
	public:
		TestMatrixOps(const std::string& name);
		~TestMatrixOps() {}

		void onUpdate(double deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Shader> m_shader;
		glm::vec3 m_translation;
		glm::mat4 m_proj, m_view;
		float m_time;
	};
}
