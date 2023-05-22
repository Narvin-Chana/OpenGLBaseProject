#include "TestCube3D.h"
#include "VertexBufferLayout.h"

test::TestCube3D::TestCube3D()
{
    projectionMatrix =
        glm::perspective(glm::radians(45.0f), (float)(960.0f / 540.0f), 0.1f, 100.0f);
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    camera = std::make_unique<Camera>();
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // unsigned int indices[] = {
    //     0, 1, 2, 3, // ABCD
    //     0, 1, 4, 5, // ABFE
    //     0, 3, 4, 7, // DAEH
    //     2, 3, 6, 7, // CDHG
    //     1, 2, 5, 6, // BCGF
    //     4, 5, 6, 7, // FGHE
    // };

    GLCall(glEnable(GL_BLEND))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCall(glEnable(GL_DEPTH_TEST))

    // Initialisation
    GLCall(glGenVertexArrays(1, &VAO))

    GLCall(glGenBuffers(1, &VBO))

    // GLCall(glGenBuffers(1, &EBO))

    // Preparation and sending of data to GPU
    // Bind VAO
    GLCall(glBindVertexArray(VAO))

    // Bind VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO))
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW))

    // Bind EBO
    // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO))
    // GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW))

    // Set the vertex attribute pointers (defines what each index in the VBO actually means)
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0))
    GLCall(glEnableVertexAttribArray(0))
    
    // Create and Bind FragmentShader & VertexShader
    shader = std::make_unique<Shader>("res\\shaders\\NoTex.vs", "res\\shaders\\NoTex.fs");
}

void test::TestCube3D::OnUpdate(float deltaTimeX, GLFWwindow* window)
{
    Test::OnUpdate(deltaTimeX, window);

    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->position += camera->cameraSpeed * camera->direction;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->position -= camera->cameraSpeed * camera->direction;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->position -= glm::normalize(glm::cross(camera->direction, camera->up)) * camera->cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->position += glm::normalize(glm::cross(camera->direction, camera->up)) * camera->cameraSpeed;
    }
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
