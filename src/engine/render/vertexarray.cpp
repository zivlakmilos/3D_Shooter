#include "engine/render/vertexarray.h"

#include <GL/glew.h>
#include <GL/gl2.h>

#include "engine/render/shader.h"
#include "engine/errors/errors.h"

zi::VertexArray::VertexArray(std::initializer_list<GLfloat> vertices,
                             std::initializer_list<GLbyte> indices)
{
    m_count = indices.size();
    
    GLfloat aVertices[m_count];
    GLbyte aIndices[m_count];
    
    int i;
    for(i = 0; i < m_count; i++)
    {
        aVertices[i] = *(vertices.begin() + i);
        aIndices[i] = *(indices.begin() + i);
    }
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

zi::VertexArray::VertexArray(void)
{
}

zi::VertexArray::~VertexArray(void)
{
    if(m_vbo)
        glDeleteBuffers(1, &m_vbo);
}

void zi::VertexArray::bind(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void zi::VertexArray::unbind(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void zi::VertexArray::setVertices(std::initializer_list<GLfloat> vertices)
{
    m_count = vertices.size();
    GLfloat arrVertices[m_count];
    
    int i;
    for(i = 0; i < m_count; i++)
        arrVertices[i] = *(vertices.begin() + i);
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertices), arrVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
