#include "engine/render/renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL/gl2.h"

#include "engine/render/shader.h"
#include "engine/errors/errors.h"

zi::Renderer::Renderer(void)
{
    glGenBuffers(1, &m_vbo);
    
    try {
        zi::Shader shader;
        shader.loadVertexShader("shader/triangletest.vertex");
        shader.loadFragmentShader("shader/triangletest.fragment");
        m_glProgram = shader.build();
    } catch(zi::ZException ex) {
        Debug::error << ex;
    }
}

zi::Renderer::~Renderer(void)
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_glProgram);
}

void zi::Renderer::setData(std::vector<GLfloat> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    
    int i;
    GLfloat arrVertices[vertices.size()];
    for(i = 0; i < vertices.size(); i++)
        arrVertices[i] = vertices[i];
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertices), arrVertices, GL_STATIC_DRAW);
}

void zi::Renderer::render(void)
{
    glUseProgram(m_glProgram);
    GLuint vertexPosition = glGetAttribLocation(m_glProgram, "vertexPosition");
    
    glEnableVertexAttribArray(vertexPosition);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(vertexPosition);
}
