#include "engine/render/vertexarray.h"

#include <GL/glew.h>
#include <GL/gl2.h>

#include "engine/render/shader.h"
#include "engine/errors/errors.h"

zi::VertexArray::VertexArray(std::initializer_list<GLfloat> vertices,
                             std::initializer_list<GLbyte> indices)
    : VertexArray()
{
    m_count = indices.size();
    if(m_count > 0)
        m_useVbi = true;
    else
        m_count = vertices.size() / 3;
    
    GLfloat aVertices[m_count];
    GLbyte aIndices[m_count];
    
    int i;
    for(i = 0; i < vertices.size(); i++)
        aVertices[i] = *(vertices.begin() + i);
    for(i = 0; i < indices.size(); i++)
        aIndices[i] = *(indices.begin() + i);
    
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(aIndices), aIndices, GL_STATIC_DRAW);
    unbind();
}

zi::VertexArray::VertexArray(void)
    : m_useVbi(false),
      m_transform(1.0f)
{
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_vbi);
    glGenBuffers(1, &m_vbc);
    glGenBuffers(1, &m_vbt);
}

zi::VertexArray::~VertexArray(void)
{
    if(m_vbo)
        glDeleteBuffers(1, &m_vbo);
    if(m_vbi)
        glDeleteBuffers(1, &m_vbi);
    if(m_vbc)
        glDeleteBuffers(1, &m_vbc);
    if(m_vbt)
        glDeleteBuffers(1, &m_vbt);
}

void zi::VertexArray::bind(int binding)
{
    if(binding & zi::VertexArray::BindVertices)
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    if(m_useVbi && binding & zi::VertexArray::BindIndices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbi);
    if(binding & zi::VertexArray::BindColors)
        glBindBuffer(GL_ARRAY_BUFFER, m_vbc);
    if(binding & zi::VertexArray::BindTextureCoords)
        glBindBuffer(GL_ARRAY_BUFFER, m_vbt);
}

void zi::VertexArray::unbind(void)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void zi::VertexArray::setVertices(std::initializer_list<GLfloat> vertices)
{
    int count = vertices.size();
    GLfloat arrVertices[count];
    if(!m_useVbi)
        m_count = count / 3;
    
    int i;
    for(i = 0; i < count; i++)
        arrVertices[i] = *(vertices.begin() + i);
    
    bind(zi::VertexArray::BindVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertices), arrVertices, GL_STATIC_DRAW);
    unbind();
}

void zi::VertexArray::setIndices(std::initializer_list<GLbyte> indices)
{
    m_count = indices.size();
    GLbyte arrIndices[m_count];
    m_useVbi = true;
    
    int i;
    for(i = 0; i < m_count; i++)
        arrIndices[i] = *(indices.begin() + i);
    
    bind(zi::VertexArray::BindIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndices), arrIndices, GL_STATIC_DRAW);
    unbind();
}

void zi::VertexArray::setColors(std::initializer_list<GLfloat> colors)
{
    GLfloat arrColors[colors.size()];
    
    int i;
    for(i = 0; i < colors.size(); i++)
        arrColors[i] = *(colors.begin() + i);
    
    bind(zi::VertexArray::BindColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arrColors), arrColors, GL_STATIC_DRAW);
    unbind();
}

void zi::VertexArray::setTextureCoords(std::initializer_list< GLfloat > textureCoords)
{
    GLfloat arrTextureCoords[textureCoords.size()];
    
    for(int i = 0; i < textureCoords.size(); i++)
        arrTextureCoords[i] = *(textureCoords.begin() + i);
    
    bind(zi::VertexArray::BindTextureCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arrTextureCoords), arrTextureCoords, GL_STATIC_DRAW);
    unbind();
}
