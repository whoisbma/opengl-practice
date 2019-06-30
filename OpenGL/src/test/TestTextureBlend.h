#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "glm/glm.hpp"

namespace test {
	class TestTextureBlend : public Test
	{
	public:
		TestTextureBlend(const std::string& name);
		~TestTextureBlend() {}

		void onUpdate(double deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_textureA, m_textureB;
		float m_blendAmt;
		glm::vec3 m_translationA;
		glm::mat4 m_proj, m_view;
	};
}

