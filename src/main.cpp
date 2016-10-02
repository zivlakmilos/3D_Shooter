#include "engine/engine.h"

#include <vector>

using namespace zi;
using namespace std;

class Window : public zi::ZWindow
{
public:
    Window(void)
        : zi::ZWindow("Test", 1024, 768),
          m_vertexArray({
              -1.0f, -1.0f, 0.0f,
               1.0f, -1.0f, 0.0f,
               0.0f,  1.0f, 0.0f
          }, {
              0, 0, 0, 0, 0, 0, 0, 0, 0
          })
    {
        vector<GLfloat> data = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f, 1.0f, 0.0f
        };
        
        int i;
        for(i = 0; i < data.size(); i++)
            m_data[i] = data[i];
        
        //m_vertexArray(data, { 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        /*
        m_vertexArray = VertexArray({
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f
        }, {
            0, 0, 0, 0, 0, 0, 0, 0, 0
        });
        */
        
        try {
            m_shader.loadVertexShader("shader/triangletest.vertex");
            m_shader.loadFragmentShader("shader/triangletest.fragment");
            m_shader.build();
        } catch(zi::ZException ex) {
            Debug::error << ex;
        }
    }
    
    virtual ~Window(void)
    {
    }
    
    virtual void render(void)
    {
        if(!m_show)
            return;
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
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
    GLfloat m_data[9];
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
