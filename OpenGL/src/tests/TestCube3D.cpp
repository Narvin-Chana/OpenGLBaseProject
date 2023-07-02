#include "TestCube3D.h"
#include "VertexBufferLayout.h"
#include "imgui/imgui.h"

test::TestCube3D::TestCube3D(GLFWwindow* w) : Test(w)
{
    projectionMatrix =
        glm::perspective(glm::radians(45.0f), (float)(960.0f / 540.0f), 0.1f, 100.0f);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    camera = std::make_unique<Camera>(window);
    camera->position = glm::vec3(0.0f, 0.0f, -3.0f);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
    };

    GLCall(glEnable(GL_BLEND))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCall(glEnable(GL_DEPTH_TEST))

    // Initialisation
    GLCall(glGenVertexArrays(1, &VAO))

    GLCall(glGenBuffers(1, &VBO))

    // Preparation and sending of data to GPU
    // Bind VAO
    GLCall(glBindVertexArray(VAO))

    // Bind VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO))
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW))

    // Set the vertex attribute pointers (defines what each index in the VBO actually means)
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0))
    GLCall(glEnableVertexAttribArray(0))

    // Create and Bind FragmentShader & VertexShader
    shader = std::make_unique<Shader>("res\\shaders\\NoTex.vs", "res\\shaders\\NoTex.fs");
}

void test::TestCube3D::OnUpdate(float deltaTime)
{
    Test::OnUpdate(deltaTime);

    camera->OnUpdate(deltaTime, window);
}

void test::TestCube3D::OnRender()
{
    Test::OnRender();

    modelMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    viewMatrix = camera->LookAt(camera->position + camera->direction);

    shader->Bind();
    shader->SetUniformMat4f("projection", projectionMatrix);
    shader->SetUniformMat4f("view", viewMatrix);
    shader->SetUniformMat4f("model", modelMatrix);

    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO))
    GLCall(glBindVertexArray(VAO))
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36))
}

void test::TestCube3D::OnImGuiRender()
{
    Test::OnImGuiRender();

    ImGui::Text(
        "Cube3D Test: Press WASD to move the camera around.\nUse MOUSE3 to activate mouse look.\nSpace to move up and CTRL to move down.");
    ImGui::Text("Camera Position: (%f, %f, %f)", camera->position.x, camera->position.y, camera->position.z);
    ImGui::Text("Camera Direction: (%f, %f, %f)", camera->direction.x, camera->direction.y, camera->direction.z);
}
