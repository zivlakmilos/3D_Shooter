#ifndef _ENGINE_Z_APPLICATION_H_
#define _ENGINE_Z_APPLICATION_H_

#include <vector>
#include <string>

namespace zi
{
    class ZWindow;
    
    class ZApplication
    {
    public:
        ZApplication(int argc, char *argv[]);
        ~ZApplication(void);
        
        virtual void addWindow(ZWindow *window);
        
        virtual void start(void);
        
    protected:
        virtual void mainLoop(void);
        
        std::vector<std::string> m_args;
        std::vector<ZWindow *> m_windows;
        bool m_running;
    };
}

#endif // _ENGINE_Z_APPLICATION_H_
