#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "glm/glm.hpp"

namespace test {
	class TestGenTexture : public Test
	{
	public:
		TestGenTexture(const std::string& name);
		~TestGenTexture() {}

		void onUpdate(double deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;
		glm::vec3 m_translationA;
		float m_scale;
		glm::mat4 m_proj, m_view;
	};
}

