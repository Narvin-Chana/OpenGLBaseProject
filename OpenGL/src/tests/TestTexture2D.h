#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "Test.h"
#include "Texture.h"


namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D() override;

        void OnUpdate(float deltaTime, GLFWwindow* window) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;

        glm::mat4 projectionMatrix, view;
        glm::vec3 translationA, translationB;
    };
}
