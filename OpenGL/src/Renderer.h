#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void DrawQuads(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

    static void Clear();
};
