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

void zi::Renderer::render(zi::VertexArray &vertexArray, zi::Shader &shader, zi::Texture *texture, glm::mat4 *transform)
{
    shader.enable();
    
    GLuint vertexPosition, vertexColor, vertexUV;
    
    try {
        vertexPosition = shader.getAttribLocation(zi::Shader::attrVertexPosition);
        if(texture)
        {
            vertexUV = shader.getAttribLocation(zi::Shader::attrVertexUV);
            shader.setUniform1f(zi::Shader::uniformFragmentTextureSampler, 0);
            texture->bind();
        } else
        {
            vertexColor = shader.getAttribLocation(zi::Shader::attrVertexColor);
        }
        if(transform)
            shader.setUniformMat4f(zi::Shader::uniformVertexTransform, *transform);
        else
            shader.setUniformMat4f(zi::Shader::uniformVertexTransform, vertexArray.getTransform());
    } catch(zi::ZException ex) {
        shader.disable();
        throw ex;
    }
    
    glEnableVertexAttribArray(vertexPosition);
    vertexArray.bind(zi::VertexArray::BindVertices |
                     zi::VertexArray::BindIndices);
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    if(texture)
    {
        glEnableVertexAttribArray(vertexUV);
        vertexArray.bind(zi::VertexArray::BindTextureCoords);
        glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    } else
    {
        glEnableVertexAttribArray(vertexColor);
        vertexArray.bind(zi::VertexArray::BindColors |
                         zi::VertexArray::BindIndices);
        glVertexAttribPointer(vertexColor, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
    
    if(vertexArray.isUseVbi())
    {
        glDrawElements(GL_TRIANGLES, vertexArray.count(), GL_UNSIGNED_BYTE, (void *)0);
    } else
    {
        glDrawArrays(GL_TRIANGLES, 0, vertexArray.count());
    }
    
    glDisableVertexAttribArray(vertexUV);
    glDisableVertexAttribArray(vertexColor);
    glDisableVertexAttribArray(vertexPosition);
    
    if(texture)
        texture->unbind();
    vertexArray.unbind();
    shader.disable();
}

void zi::Renderer::render(zi::Camera &camera, zi::VertexArray &vertexArray,
                          zi::Shader &shader, zi::Texture *texture)
{
    glm::mat4 transform = camera.getTransform() * vertexArray.getTransform();
    
    render(vertexArray, shader, texture, &transform);
}

void zi::Renderer::render(zi::VertexArray &vertexArray, zi::Shader &shader, zi::Texture *texture)
{
    render(vertexArray, shader, texture, nullptr);
}
