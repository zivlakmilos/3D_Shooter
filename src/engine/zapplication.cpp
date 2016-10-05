#include "engine/zapplication.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/errors/errors.h"
#include "engine/zwindow.h"

using namespace std;

zi::ZApplication::ZApplication(int argc, char *argv[])
    : m_running(false)
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
}

zi::ZApplication::~ZApplication(void)
{
    int i;
    for(i = 0; i < m_windows.size(); i++)
        delete m_windows[i];
    
    glfwTerminate();
}

void zi::ZApplication::addWindow(zi::ZWindow *window)
{
    m_windows.push_back(window);
}

void zi::ZApplication::start(void)
{
    m_running = true;
    m_lastTime = glfwGetTime();
    mainLoop();
}

void zi::ZApplication::mainLoop(void)
{
    int i;
    
    while(m_running)
    {
        /*
         * Calculating delta time
         */
        double currentTime = glfwGetTime();
        double deltaTime = m_lastTime - currentTime;
        m_lastTime = currentTime;
        
        for(i = 0; i < m_windows.size(); i++)
        {
            if(!m_windows[i]->isShowing())
                continue;
            
            m_windows[i]->updateTime(deltaTime);
            m_windows[i]->logic();
            if(m_windows[i]->shouldClose())
            {
                delete m_windows[i];
                m_windows.erase(m_windows.begin() + i--);
                continue;
            }
                
            m_windows[i]->render();
        }
        if(m_windows.empty())
            m_running = false;
    }
}
