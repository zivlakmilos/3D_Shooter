#include "engine/zapplication.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/errors/errors.h"

using namespace std;

zi::ZApplication::ZApplication(int argc, char *argv[])
{
    int i;
    for(i = 0; i < argc; i++)
    {
        string arg = argv[i];
        m_args.push_back(arg);
    }
    
    if(!glfwInit())
        throw ZException("Can't initialize glfw");
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

zi::ZApplication::~ZApplication(void)
{
    glfwTerminate();
}
