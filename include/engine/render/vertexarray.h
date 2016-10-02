#ifndef _ENGINE_RENDER_VERTEX_ARRAY_H_
#define _ENGINE_RENDER_VERTEX_ARRAY_H_

#include <initializer_list>
#include <GL/glew.h>

#include "engine/render/shader.h"

namespace zi
{
    class VertexArray
    {
    public:
        VertexArray(std::initializer_list<GLfloat> vertices,
                    std::initializer_list<GLbyte> indices);
        VertexArray(void);
        virtual ~VertexArray(void);
        
        void bind(void);
        void unbind(void);
        
        void setVertices(std::initializer_list<GLfloat> vertices);
        void setIndices(std::initializer_list<GLbyte> indices);
        
    private:
        int m_count;
        
        GLuint m_vbo;
        GLuint m_vbi;
    };
}

#endif // _ENGINE_RENDER_VERTEX_ARRAY_H_
