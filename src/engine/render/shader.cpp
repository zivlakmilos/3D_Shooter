#include "engine/render/shader.h"

#include <fstream>
#include <GL/glew.h>
#include <GL/gl2.h>

#include <engine/errors/errors.h>

const std::string zi::Shader::attrVertexPosition = "vertexPosition";
const std::string zi::Shader::attrVertexColor = "vertexColor";
const std::string zi::Shader::attrVertexUV = "vertexUV";
const std::string zi::Shader::uniformVertexTransform = "vertexTransform";
const std::string zi::Shader::uniformFragmentTextureSampler = "fragmentTextureSampler";

zi::Shader::Shader(void)
{
    m_glProgram = glCreateProgram();
}

zi::Shader::~Shader(void)
{
    if(m_glProgram)
        glDeleteProgram(m_glProgram);
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

void zi::Shader::build(void)
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
    
    glAttachShader(m_glProgram, vertexShader);
    glAttachShader(m_glProgram, fragmentShader);
    glLinkProgram(m_glProgram);
    
    glDetachShader(m_glProgram, vertexShader);
    glDetachShader(m_glProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLint ok = GL_FALSE;
    glGetProgramiv(m_glProgram, GL_LINK_STATUS, &ok);
    if(ok == GL_FALSE)
    {
        glDeleteProgram(m_glProgram);
        int logSize;
        glGetProgramiv(m_glProgram, GL_INFO_LOG_LENGTH, &logSize);
        if(logSize > 0)
        {
            char log[logSize + 1];
            glGetProgramInfoLog(m_glProgram, logSize, 0, log);
            std::string msg = "Shader linking error: ";
            msg += log;
            throw zi::ZException(msg);
        } else
            throw zi::ZException("Shader linking error: Unknown");
    }
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

GLuint zi::Shader::compileShader(GLenum shaderType, std::string &shaderCode)
{
    if(shaderCode.empty())
        throw zi::ZException("Shader code not loaded");
    
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
            throw zi::ZException("Shader compiling error: Unknown");
    }
    
    return result;
}

void zi::Shader::enable(void)
{
    glUseProgram(m_glProgram);
}

void zi::Shader::disable(void)
{
    glUseProgram(0);
}

GLint zi::Shader::getUniformLocation(std::string name) const
{
    GLint result;
    result = glGetUniformLocation(m_glProgram, name.c_str());
    if(result < 0)
        throw zi::ZException("Uniform with name \"" + name + "\" don't exists in shader");
    return result;
}

void zi::Shader::setUniform3f(std::string name, glm::vec3 value)
{
    try {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    } catch(zi::ZException ex) {
        throw ex;
    }
}

GLint zi::Shader::getAttribLocation(std::string name) const
{
    GLint result;
    result = glGetAttribLocation(m_glProgram, name.c_str());
    if(result < 0)
        throw zi::ZException("Attribute with name \"" + name + "\" don't exists in shader");
    return result;
}

void zi::Shader::setUniformMat4f(std::string name, glm::mat4 value)
{
    try {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    } catch(zi::ZException ex) {
        throw ex;
    }
}

void zi::Shader::setUniform1f(std::string name, GLfloat value)
{
    try {
        glUniform1f(getUniformLocation(name), value);
    } catch(zi::ZException ex) {
        throw ex;
    }
}
