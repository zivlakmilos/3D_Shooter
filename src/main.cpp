#include "engine/engine.h"

using namespace zi;

int main(int argc, char *argv[])
{
    /*
     * Must init before create object of ZApllication
     */
    Debug::init();
    Debug::setDebugEnabled(true);
    
    try {
        ZApplication app(argc, argv);
        ZWindow *window = new ZWindow("Test", 1024, 768);
        ZWindow *window2 = new ZWindow("Test2", 1024, 768);
        app.addWindow(window);
        app.addWindow(window2);
        window->show();
        window2->show();
        app.start();
    } catch(ZException ex) {
        Debug::error << ex;
    }
    
    return 0;
}
