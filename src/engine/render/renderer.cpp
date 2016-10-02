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
    shader.setUniformMat4f(zi::Shader::uniformVertexTransform, vertexArray.getTransform());
    
    glEnableVertexAttribArray(vertexPosition);
    
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    if(vertexArray.isUseVbi())
    {
        glDrawElements(GL_TRIANGLES, vertexArray.count(), GL_UNSIGNED_BYTE, (void *)0);
    } else
    {
        glDrawArrays(GL_TRIANGLES, 0, vertexArray.count());
    }
    
    glDisableVertexAttribArray(vertexPosition);
    
    vertexArray.unbind();
    shader.disable();
}
