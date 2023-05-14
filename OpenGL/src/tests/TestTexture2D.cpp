#include "TestTexture2D.h"

#include "imgui/imgui.h"
#include "Texture.h"
#include "VertexBufferLayout.h"


namespace test
{
    TestTexture2D::TestTexture2D() : projectionMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
                                     view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
                                     translationA(200, 200, 0),
                                     translationB(200, 400, 0)
    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f, // Vert0
            50.0f, -50.0f, 1.0f, 0.0f, // Vert1
            50.0f, 50.0f, 1.0f, 1.0f, // Vert2
            -50.0f, 50.0f, 0.0f, 1.0f, // Vert3
        };

        unsigned int indices[] = {
            0, 1, 2, // First triangle
            2, 3, 0 // Second triangle
        };

        GLCall(glEnable(GL_BLEND))
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

        vertexArray = std::make_unique<VertexArray>();

        vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        vertexArray->AddBuffer(*vertexBuffer, layout);

        indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        shader = std::make_unique<Shader>("res\\shaders\\Tex.vs", "res\\shaders\\Tex.fs");
        shader->Bind();

        texture = std::make_unique<Texture>("res/textures/Oranges.png");
        shader->SetUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D() = default;

    void TestTexture2D::OnUpdate(float deltaTime)
    {
        Test::OnUpdate(deltaTime);
    }

    void TestTexture2D::OnRender()
    {
        Test::OnRender();
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f))
        GLCall(glClear(GL_COLOR_BUFFER_BIT))

        texture->Bind();

        {
            const glm::mat4 model = translate(glm::mat4(1.0f), translationA);
            const glm::mat4 mvp = projectionMatrix * view * model;
            shader->Bind();
            shader->SetUniformMat4f("u_MVP", mvp);
            Renderer::Draw(*vertexArray, *indexBuffer, *shader);
        }
        {
            const glm::mat4 model = translate(glm::mat4(1.0f), translationB);
            const glm::mat4 mvp = projectionMatrix * view * model;
            shader->Bind();
            shader->SetUniformMat4f("u_MVP", mvp);
            Renderer::Draw(*vertexArray, *indexBuffer, *shader);
        }
    }

    void TestTexture2D::OnImGuiRender()
    {
        Test::OnImGuiRender();
        ImGui::SliderFloat3("Translation1", &translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation2", &translationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
    }
}
