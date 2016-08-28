#include "engine/zapplication.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

zi::ZApplication::ZApplication(int argc, char *argv[])
{
    int i;
    for(i = 0; i < argc; i++)
    {
        string arg = argv[i];
        m_args.push_back(arg);
    }
    
    if(!glfwInit());
        // Exception
}

zi::ZApplication::~ZApplication(void)
{
    glfwTerminate();
}
