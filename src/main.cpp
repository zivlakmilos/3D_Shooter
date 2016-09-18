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
    } catch(ZException ex) {
        Debug::error << ex;
    }
    
    return 0;
}
