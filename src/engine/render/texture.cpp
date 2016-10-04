#include "engine/render/texture.h"

#include <vector>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <png.h>
#include "GL/gl2.h"

#include "engine/errors/errors.h"
#include "engine/core/memory/memory.h"

/*
 * TODO:
 *  Can (must) be inheritence from BaseCResourceHandler
 */
class PngStructHandler
{
public:
    PngStructHandler(void)
        : m_pStruct(NULL),
          m_pInfo1(NULL),
          m_pInfo2(NULL) {};
    virtual ~PngStructHandler(void)
    {
        png_destroy_read_struct(m_pStruct,
                                m_pInfo1,
                                m_pInfo2);
    };
    
    void inline setStruct(png_structpp pStruct) { m_pStruct = pStruct; };
    void inline setInfo1(png_infopp pInfo) { m_pInfo1 = pInfo; };
    void inline setInfo2(png_infopp pInfo) { m_pInfo2 = pInfo; };
    
private:
    png_structpp m_pStruct;
    png_infopp m_pInfo1;
    png_infopp m_pInfo2;
};

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

/*
 * TODO:
 *  Make new class for holding data image, and then just use it from here
 *  (for threading)
 */
void zi::Texture::load(std::string filePath)
{
    char header[8];
    PngStructHandler pngHandler;
    
    FILE *fd = fopen(filePath.c_str(), "rb");
    if(!fd)
        throw zi::ZException("Can't open PNG file \"" + filePath + "\"");
    zi::CFileHandler fileHandler(fd);
    
    fread(header, 1, 8, fd);
    
    if(png_sig_cmp((png_bytep) header, 0, 8))
        throw zi::ZException("File is not a PNG image");
    
    png_structp pPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!pPng)
        throw zi::ZException("Can't create PNG struct");
    pngHandler.setStruct(&pPng);
    
    png_infop pInfo = png_create_info_struct(pPng);
    if(!pInfo)
        throw zi::ZException("Can't create PNG info struct");
    pngHandler.setInfo1(&pInfo);
    
    png_infop pEndInfo = png_create_info_struct(pPng);
    if(!pInfo)
        throw zi::ZException("Can't create PNG info struct");
    pngHandler.setInfo1(&pEndInfo);
    
    if(setjmp(png_jmpbuf(pPng)))
        throw zi::ZException("Error while loading PNG");
    
    png_init_io(pPng, fd);
    png_set_sig_bytes(pPng, 8);
    png_read_info(pPng, pInfo);
    
    int bitDepth, colorType;
    png_uint_32 width, height;
    
    png_get_IHDR(pPng, pInfo, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);
    
    png_read_update_info(pPng, pInfo);
    int rowBytes = png_get_rowbytes(pPng, pInfo);
    
    std::vector<png_byte> imageData(rowBytes * height);
    
    png_bytep *rowPointers = new png_bytep[height];
    std::vector<png_bytep> rawPointers(height);
    
    int i;
    for(i = 0; i < height; i++)
        rowPointers[height - 1 - i] = &imageData[0] + i * rowBytes;
    
    png_read_image(pPng, rowPointers);
    
    /*
     * Now generateing texture for OpenGL
     */
    
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)&imageData[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
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
