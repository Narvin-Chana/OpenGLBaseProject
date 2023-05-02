#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (const GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    // Rebind shader
    shader.Bind();

    // Bind vertex array object
    va.Bind();
    // Bind index buffer
    ib.Bind();
    // Draw triangles
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr))
}

void Renderer::Clear()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f))
    GLCall(glClear(GL_COLOR_BUFFER_BIT))
}
