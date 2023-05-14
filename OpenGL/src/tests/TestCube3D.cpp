#include "TestCube3D.h"
#include "VertexBufferLayout.h"

test::TestCube3D::TestCube3D() : projectionMatrix(
                                     glm::perspective(glm::radians(45.0f), (float)(960.0f / 540.0f), 0.1f, 100.0f)),
                                 translation(0, 0, 0)
{
    glm::vec3 cameraPos(0, 0, 20);
    glm::vec3 cameraFront(0, 0, -1);
    glm::vec3 cameraUp(0, 1, 0);
    view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    float vertices[] = {
        -5.0f, 5.0f, -5.0f, // Vert0 | A
        -5.0f, -5.0f, -5.0f, // Vert1 | B
        5.0f, -5.0f, -5.0f, // Vert2 | C
        5.0f, 5.0f, -5.0f, // Vert3 | D
        -5.0f, 5.0f, 5.0f, // Vert4 | E
        -5.0f, -5.0f, 5.0f, // Vert5 | F
        5.0f, -5.0f, 5.0f, // Vert6 | G
        5.0f, 5.0f, 5.0f, // Vert7 | H
    };

    unsigned int indices[] = {
        0, 1, 2, 3, // ABCD
        0, 1, 4, 5, // ABFE
        0, 3, 4, 7, // DAEH
        2, 3, 6, 7, // CDHG
        1, 2, 5, 6, // BCGF
        4, 5, 6, 7, // FGHE
    };

    GLCall(glEnable(GL_BLEND))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCall(glEnable(GL_DEPTH_TEST))

    // Initialisation
    unsigned int VAO;
    GLCall(glGenVertexArrays(1, &VAO))

    unsigned int VBO;
    GLCall(glGenBuffers(1, &VBO))

    unsigned int EBO;
    GLCall(glGenBuffers(1, &EBO))

    // Preparation and sending of data to GPU
    // Bind VAO
    GLCall(glBindVertexArray(VAO))

    // Bind VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO))
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW))

    // Bind EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO))
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW))

    // Set the vertex attribute pointers (defines what each index in the VBO actually means)
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0))
    GLCall(glEnableVertexAttribArray(0))

    const glm::mat4 model = translate(glm::mat4(1.0f), translation);
    const glm::mat4 mvp = projectionMatrix * view * model;
    // Create and Bind FragmentShader & VertexShader
    shader = std::make_unique<Shader>("res\\shaders\\NoTex.vs", "res\\shaders\\NoTex.fs");
    shader->Bind();
    shader->SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", mvp);
    
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO))
    GLCall(glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0))
    // indexBuffer = std::make_unique<IndexBuffer>(indices, 24);
}

void test::TestCube3D::OnUpdate(float deltaTime)
{
    Test::OnUpdate(deltaTime);
}

void test::TestCube3D::OnRender()
{
    Test::OnRender();

    // const glm::mat4 model = translate(glm::mat4(1.0f), translation);
    // const glm::mat4 mvp = projectionMatrix * view * model;
    // shader->Bind();
    // shader->SetUniformMat4f("u_MVP", mvp);
    // Renderer::DrawQuads(*vertexArray, *indexBuffer, *shader);
}
