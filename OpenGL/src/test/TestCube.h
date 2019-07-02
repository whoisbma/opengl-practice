#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "glm/glm.hpp"

namespace test {
	class TestCube : public Test
	{
	public:
		TestCube(const std::string& name);
		~TestCube() {}

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
		float m_blendAmt;

		std::unique_ptr<Texture> m_textureA, m_textureB;

		glm::vec3 m_transform;

		float m_fov;
		glm::vec3 m_camera;
		glm::vec3 m_target;
		glm::vec3 m_upAxis;
	};
}
