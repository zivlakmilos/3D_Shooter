#include "engine/render/texture.h"

#include <vector>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <png.h>
#include "GL/gl2.h"

#include "engine/errors/errors.h"
#include "engine/core/memory/memory.h"
#include "engine/core/pngimage.h"

zi::Texture::Texture(zi::PngImage &pngImage)
    : Texture()
{
    try {
        load(pngImage);
    } catch(zi::ZException ex) {
        throw ex;
    }
}

zi::Texture::Texture(std::string filePath)
    : Texture()
{
    try {
        load(filePath);
    } catch(zi::ZException ex) {
        throw ex;
    }
}

zi::Texture::Texture(void)
{
    glGenTextures(1, &m_texture);
}

zi::Texture::~Texture(void)
{
    if(m_texture)
        glDeleteTextures(1, &m_texture);
}

void zi::Texture::load(zi::PngImage &pngImage)
{
    std::vector<png_byte> imageData = pngImage.getData();
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngImage.getWidth(), pngImage.getHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)&imageData[0]);
    setParameterf(GL_TEXTURE_WRAP_S, GL_REPEAT);
    setParameterf(GL_TEXTURE_WRAP_T, GL_REPEAT);
    setParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    setParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
}

void zi::Texture::load(std::string filePath)
{
    PngImage texImage;
    
    try {
        texImage.load(filePath);
        load(texImage);
    } catch(zi::ZException ex) {
        throw ex;
    }
}

void zi::Texture::bind(void)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void zi::Texture::unbind(void)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void zi::Texture::setParameteri(GLenum parameter, GLint value)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, parameter, value);
    unbind();
}

void zi::Texture::setParameterf(GLenum parameter, GLint value)
{
    bind();
    glTexParameterf(GL_TEXTURE_2D, parameter, value);
    unbind();
}
