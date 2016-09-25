#include "engine/engine.h"

#include <vector>

using namespace zi;
using namespace std;

class Window : public zi::ZWindow
{
public:
    Window(void)
        : zi::ZWindow("Test", 1024, 768)
    {
        vector<GLfloat> data = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f, 1.0f, 0.0f
        };
        renderer.setData(data);
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
        
        renderer.render();
        
        zi::ZWindow::render();
    }
    
private:
    Renderer renderer;
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
