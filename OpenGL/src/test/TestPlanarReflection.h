#pragma once

#include "Test.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>
#include "glm/glm.hpp"

namespace test {
	class TestPlanarReflection : public Test
	{
	public:
		TestPlanarReflection(const std::string& name);
		~TestPlanarReflection() {}

		void onUpdate(double deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO, m_floorVAO;
		std::unique_ptr<IndexBuffer> m_indexBuffer, m_floorIndexBuffer;
		std::unique_ptr<VertexBuffer> m_vertexBuffer, m_floorVertexBuffer;
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
