#ifndef _ENGINE_RENDER_SHADER_
#define _ENGINE_RENDER_SHADER_

#include <string>
#include <GL/glew.h>

namespace zi
{
    class Shader
    {
    public:
        Shader(void);
        virtual ~Shader(void);
        
        void loadVertexShader(std::string vertexFileName);
        void loadFragmentShader(std::string fragmentFileName);
        GLuint build(void);
        
    private:
        void loadShader(std::string shaderFileName, std::string &shaderCode);
        GLuint compileShader(GLenum shaderType, std::string shaderCode);
        
        std::string m_vertexShaderCode;
        std::string m_fragmentShaderCode;
        
        enum ExceptionCodes {
            ExceptionShaderNotLoaded = 1,
            ExceptionShaderUnknown
        };
    };
};

#endif // _ENGINE_RENDER_SHADER_
