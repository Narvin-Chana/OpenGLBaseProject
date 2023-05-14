#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath) : vertexFilePath(vertexFilepath), fragmentFilePath(fragmentFilepath), rendererID(0)
{
    ShaderProgramSource source = ParseShader(vertexFilepath, fragmentFilepath);
    rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(rendererID))
}

ShaderProgramSource Shader::ParseShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) const
{
    std::ifstream vStream(vertexFilepath);
    std::ifstream fStream(fragmentFilepath);

    std::string line;
    std::stringstream ss[2];
    while (getline(vStream, line))
    {
        ss[0] << line << '\n';
    }
    while (getline(fStream, line))
    {
        ss[1] << line << '\n';
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(const unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type))
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr))
    GLCall(glCompileShader(id))

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result))

    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length))

        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message))

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id))
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram())

    // Create shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs))
    GLCall(glAttachShader(program, fs))
    GLCall(glLinkProgram(program))
    GLCall(glValidateProgram(program))

    GLCall(glDeleteShader(vs))
    GLCall(glDeleteShader(fs))

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(rendererID))
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0))
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value))
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value))
}

void Shader::SetUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3))
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]))
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
    {
        return uniformLocationCache[name];
    }

    GLCall(const int location = glGetUniformLocation(rendererID, name.c_str()))
    ASSERT(location != -1)
    uniformLocationCache[name] = location;
    return location;
}
