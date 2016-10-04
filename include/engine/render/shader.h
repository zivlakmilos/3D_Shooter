#ifndef _ENGINE_RENDER_SHADER_
#define _ENGINE_RENDER_SHADER_

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace zi
{
    class Shader
    {
    public:
        Shader(void);
        virtual ~Shader(void);
        
        void loadVertexShader(std::string vertexFileName);
        void loadFragmentShader(std::string fragmentFileName);
        void build(void);
        void enable(void);
        void disable(void);
        
        GLint getUniformLocation(std::string name) const;
        GLint getAttribLocation(std::string name) const;
        
        void setUniform3f(std::string name, glm::vec3 value);
        void setUniformMat4f(std::string name, glm::mat4 value);
        void setUniform1f(std::string name, GLfloat value);
        
        static const std::string attrVertexPosition;
        static const std::string attrVertexColor;
        static const std::string attrVertexUV;
        static const std::string uniformVertexTransform;
        static const std::string uniformFragmentTextureSampler;
        
    private:
        void loadShader(std::string shaderFileName, std::string &shaderCode);
        GLuint compileShader(GLenum shaderType, std::string &shaderCode);
        
        std::string m_vertexShaderCode;
        std::string m_fragmentShaderCode;
        GLuint m_glProgram;
    };
}

#endif // _ENGINE_RENDER_SHADER_
