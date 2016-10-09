#ifndef _ENGINE_RENDER_TEXTURE_H_
#define _ENGINE_RENDER_TEXTURE_H_

#include <string>
#include <GL/glew.h>

#include "engine/core/pngimage.h"

namespace zi
{
    class Texture
    {
    public:
        Texture(zi::PngImage &pngImage);
        Texture(std::string filePath);
        Texture(void);
        virtual ~Texture(void);
        
        void load(zi::PngImage &pngImage);
        void load(std::string filePath);
        void bind(void);
        void unbind(void);
        
        void setParameteri(GLenum parameter, GLint value);
        void setParameterf(GLenum parameter, GLint value);
        
    private:
        GLuint m_texture;
    };
}

#endif // _ENGINE_RENDER_TEXTURE_H_
