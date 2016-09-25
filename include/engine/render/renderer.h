#ifndef _ENGINE_RENDER_RENDERER_H_
#define _ENGINE_RENDER_RENDERER_H_

#include <GL/glew.h>
#include <vector>

namespace zi
{
    class Renderer
    {
    public:
        Renderer(void);
        virtual ~Renderer(void);
        
        void setData(std::vector<GLfloat> vectices);
        void render(void);
        
    private:
        GLuint m_glProgram;
        GLuint m_vbo;
    };
}

#endif // _ENGINE_RENDER_RENDERER_H_
