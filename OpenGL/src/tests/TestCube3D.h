#pragma once
#include "IndexBuffer.h"
#include "Shader.h"
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace test
{
    class TestCube3D : public Test
    {
    public:
        TestCube3D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;

    private:
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<VertexArray> vertexArray;
        std::unique_ptr<IndexBuffer> indexBuffer;
        std::unique_ptr<Shader> shader;

        glm::mat4 projectionMatrix, view;
        glm::vec3 translation;
    };
}
