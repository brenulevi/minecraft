#include "texture.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture()
    : _width(0), _height(0), _channels(0)
{
    glGenTextures(1, &_id);

    set_filtering(GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
    set_wrapping(GL_REPEAT, GL_REPEAT);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}

void Texture::load_image(const char *path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &_width, &_height, &_channels, 4);

    if(data)
    {
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "invalid texture path: " << path << std::endl;
    }
}

void Texture::set_filtering(int min, int mag)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture::set_wrapping(int s, int t)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _id);
}
