#include "TestCube3D.h"
#include "VertexBufferLayout.h"

test::TestCube3D::TestCube3D() : projectionMatrix(
                                     glm::perspective(glm::radians(45.0f), (float)(960.0f / 540.0f), 1.0f, 100.0f)),
                                 translation(0, 0, 0)
{
    glm::vec3 cameraPos(0, 0, 20);
    glm::vec3 cameraFront(0, 0, -1);
    glm::vec3 cameraUp(0, 1, 0);
    view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    float positions[] = {
        -5.0f, 5.0f, -5.0f, // Vert0 | A
        5.0f, 5.0f, -5.0f, // Vert1 | B
        5.0f, 5.0f, 5.0f, // Vert2 | C
        -5.0f, 5.0f, 5.0f, // Vert3 | D

        -5.0f, -5.0f, -5.0f, // Vert4 | A1
        5.0f, -5.0f, -5.0f, // Vert5 | B1
        5.0f, -5.0f, 5.0f, // Vert6 | C1
        -5.0f, -5.0f, 5.0f // Vert7 | D1
    };

    unsigned int indices[] = {
        0, 1, 2, // ABC
        2, 3, 0, // ADC
        4, 7, 5, // A1D1B1
        5, 7, 6, // B1D1C1
        0, 3, 4, // ADA1
        4, 3, 7, // A1DD1
        1, 5, 6, // BB1C1
        1, 6, 2, // BC1C
        6, 7, 2, // C1D1C
        2, 7, 3, // CD1D
        4, 5, 0, // A1B1A
        0, 5, 1, // AB1B
    };

    GLCall(glEnable(GL_BLEND))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCall(glEnable(GL_DEPTH_TEST))

    vertexArray = std::make_unique<VertexArray>();

    vertexBuffer = std::make_unique<VertexBuffer>(positions, 3 * 8 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);

    vertexArray->AddBuffer(*vertexBuffer, layout);

    indexBuffer = std::make_unique<IndexBuffer>(indices, 12);

    shader = std::make_unique<Shader>("res\\shaders\\NoTex.shader");
    shader->Bind();
    shader->SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
}

void test::TestCube3D::OnUpdate(float deltaTime)
{
    Test::OnUpdate(deltaTime);
}

void test::TestCube3D::OnRender()
{
    Test::OnRender();

    const glm::mat4 model = translate(glm::mat4(1.0f), translation);
    const glm::mat4 mvp = projectionMatrix * view * model;
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", mvp);
    Renderer::Draw(*vertexArray, *indexBuffer, *shader);
}
