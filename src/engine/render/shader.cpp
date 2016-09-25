#include "engine/render/shader.h"

#include <fstream>
#include <GL/glew.h>
#include <GL/gl2.h>

#include <engine/errors/errors.h>

zi::Shader::Shader(void)
{
}

zi::Shader::~Shader(void)
{
}

void zi::Shader::loadVertexShader(std::string vertexFileName)
{
    try {
        loadShader(vertexFileName, m_vertexShaderCode);
    } catch(zi::ZException ex) {
        throw zi::ZException("Can't load vertex shader: " + vertexFileName);
    }
}

void zi::Shader::loadFragmentShader(std::string fragmentFileName)
{
    try {
        loadShader(fragmentFileName, m_fragmentShaderCode);
    } catch(zi::ZException ex) {
        throw zi::ZException("Can't load fragment shader: " + fragmentFileName);
    }
}

GLuint zi::Shader::build(void)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    
    try {
        vertexShader = compileShader(GL_VERTEX_SHADER, m_vertexShaderCode);
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, m_fragmentShaderCode);
    } catch(zi::ZException ex) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        std::string msg = "Can't compile shaders\n    ";
        msg += ex.what();
        throw zi::ZException(msg);
    }
    
    /*
     * Linking program
     */
    GLuint program = glCreateProgram();
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLint ok = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if(ok == GL_FALSE)
    {
        glDeleteProgram(program);
        int logSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        if(logSize > 0)
        {
            char log[logSize + 1];
            glGetProgramInfoLog(program, logSize, 0, log);
            std::string msg = "Shader linking error: ";
            msg += log;
            throw zi::ZException(log);
        } else
            throw zi::ZException("Shader linking error: Unknown");
    }
    
    return program;
}

void zi::Shader::loadShader(std::string shaderFileName, std::string &shaderCode)
{
    std::ifstream shaderStream(shaderFileName, std::ios::in);
    
    if(!shaderStream.is_open())
    {
        throw zi::ZException("Can't open shader: " + shaderFileName);
    }
    
    std::string line;
    
    shaderCode.clear();
    while(std::getline(shaderStream, line))
        shaderCode += line + "\n";
    shaderStream.close();
}

GLuint zi::Shader::compileShader(GLenum shaderType, std::string shaderCode)
{
    if(shaderCode.empty())
        throw zi::ZException("Shader code not loaded", zi::Shader::ExceptionShaderNotLoaded);
    
    GLuint result = glCreateShader(shaderType);
    
    const char *pShaderCode = shaderCode.c_str();
    glShaderSource(result, 1, &pShaderCode, NULL);
    glCompileShader(result);
    
    GLint ok = GL_FALSE;
    glGetShaderiv(result, GL_COMPILE_STATUS, &ok);
    if(ok == GL_FALSE)
    {
        glDeleteShader(result);
        int logSize;
        glGetShaderiv(result, GL_INFO_LOG_LENGTH, &logSize);
        if(logSize > 0)
        {
            char log[logSize + 1];
            glGetShaderInfoLog(result, logSize, 0, log);
            std::string msg = "Shader compiling error: ";
            msg += log;
            throw zi::ZException(msg);
        } else
            throw zi::ZException("Shader compiling error: Unknown", zi::Shader::ExceptionShaderUnknown);
    }
    
    return result;
}
