#ifndef _ENGINE_Z_WINDOW_H_
#define _ENGINE_Z_WINDOW_H_

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace zi
{
    class ZWindow
    {
    public:
        ZWindow(std::string caption, int width, int height);
        virtual ~ZWindow(void);
        
        virtual void logic(void);
        virtual void render(void);
        
        virtual void show(bool show = true);
        virtual bool shouldClose(void) const { return !m_alive; };
        
    protected:
        std::string m_caption;
        int m_width;
        int m_height;
        GLFWwindow *m_glfwWindow;
        bool m_show;
        bool m_alive;
    };
}

#endif // _ENGINE_Z_WINDOW_H_
