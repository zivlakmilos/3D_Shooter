#include "engine/zwindow.h"

#include "engine/errors/errors.h"

zi::ZWindow::ZWindow(std::string caption, int width, int height)
    : m_caption(caption),
      m_width(width),
      m_height(height),
      m_show(false),
      m_alive(true)
{
    m_glfwWindow = glfwCreateWindow(width, height, caption.c_str(), NULL, NULL);
    if(m_glfwWindow == NULL)
        throw ZException("Can't open GLFW window");
    
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSetInputMode(m_glfwWindow, GLFW_STICKY_KEYS, GL_TRUE);
    
    if(glewInit() != GLEW_OK)
        throw ZException("Can't initialize GLEW");
    
    glfwHideWindow(m_glfwWindow);
}

zi::ZWindow::~ZWindow(void)
{
    glfwDestroyWindow(m_glfwWindow);
}

void zi::ZWindow::render(void)
{
    if(!m_show)
        return;
    
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSwapBuffers(m_glfwWindow);
    glfwPollEvents();
}

void zi::ZWindow::logic(void)
{
    if(!m_show)
        return;
    
    glfwMakeContextCurrent(m_glfwWindow);
    if(glfwWindowShouldClose(m_glfwWindow) ||
       glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        m_alive = false;
}

void zi::ZWindow::show(bool show)
{
    m_show = show;
    
    if(show)
        glfwShowWindow(m_glfwWindow);
    else
        glfwHideWindow(m_glfwWindow);
}
