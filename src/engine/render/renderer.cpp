#include "engine/render/renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL/gl2.h"

#include "engine/render/shader.h"
#include "engine/render/vertexarray.h"
#include "engine/errors/errors.h"

zi::Renderer::Renderer(void)
{
}

zi::Renderer::~Renderer(void)
{
}

void zi::Renderer::render(zi::VertexArray &vertexArray, zi::Shader &shader)
{
    shader.enable();
    vertexArray.bind();
    
    GLuint vertexPosition = shader.getAttribLocation(zi::Shader::attrVertexPosition);
    
    glEnableVertexAttribArray(vertexPosition);
    
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(vertexPosition);
    
    vertexArray.unbind();
    shader.disable();
}
