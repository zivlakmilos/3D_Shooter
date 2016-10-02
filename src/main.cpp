#include "engine/engine.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace zi;
using namespace std;

class Window : public zi::ZWindow
{
public:
    Window(void)
        : zi::ZWindow("Test", 1024, 768)
    {
        m_vertexArray.setVertices({
             -1.0f, -1.0f, -1.0f,
              1.0f, -1.0f, -1.0f,
              1.0f,  1.0f, -1.0f,
             -1.0f,  1.0f, -1.0f,
             -1.0f, -1.0f,  1.0f,
              1.0f, -1.0f,  1.0f,
              1.0f,  1.0f,  1.0f,
             -1.0f,  1.0f,  1.0f,
        });
        m_vertexArray.setColors({
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f
        });
        m_vertexArray.setIndices({
            0, 1, 2,    2, 3, 0,    // Front
            4, 5, 6,    6, 7, 4,    // Back
            1, 5, 6,    6, 2, 1,    // Left
            0, 3, 7,    7, 4, 0,    // Right
            0, 1, 5,    5, 3, 0,    // Bottom
            3, 2, 6,    6, 7, 3     // Top
        });
        
        glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(4, 3, -3),
                                     glm::vec3(0, 0, 0),
                                     glm::vec3(0, 1, 0));
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 transform = projection * view * model;
        
        m_vertexArray.setTransform(transform);
        
        try {
            m_shader.loadVertexShader("shader/triangletest.vertex");
            m_shader.loadFragmentShader("shader/triangletest.fragment");
            m_shader.build();
        } catch(zi::ZException ex) {
            Debug::error << ex;
        }
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    
    virtual ~Window(void)
    {
    }
    
    virtual void render(void)
    {
        if(!m_show)
            return;
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        try {
            m_renderer.render(m_vertexArray, m_shader);
        } catch(zi::ZException ex) {
            Debug::error << ex;
        }
        
        zi::ZWindow::render();
    }
    
private:
    VertexArray m_vertexArray;
    Shader m_shader;
    Renderer m_renderer;
};

int main(int argc, char *argv[])
{
    /*
     * Must init before create object of ZApllication
     */
    Debug::init();
    Debug::setDebugEnabled(true);
    
    try {
        ZApplication app(argc, argv);
        Window *window = new Window;
        app.addWindow(window);
        window->show();
        app.start();
    } catch(ZException ex) {
        Debug::error << ex;
    }
    
    return 0;
}
