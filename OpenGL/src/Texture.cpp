#include "Texture.h"

#include "stb_image/stb_image.h"

enum
{
    rgba_channel_count = 4
};

Texture::Texture(const std::string& path) : rendererID(0), filePath(path), localBuffer(nullptr), width(0),
                                            height(0), BPP(0)
{
    // Flip because OpenGL for some reason decides that (0,0) is bottom-left
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, rgba_channel_count);

    GLCall(glGenTextures(1, &rendererID))
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID))

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer))
    Unbind();

    if (localBuffer)
    {
        stbi_image_free(localBuffer);
    }
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &rendererID))
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot))
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID))
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0))
}
