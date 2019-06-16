#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "glm/glm.hpp"

namespace test {
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D(const std::string& name);
		~TestTexture2D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;
		glm::vec3 m_translationA, m_translationB;
		glm::mat4 m_proj, m_view;
	};
}

