#ifndef _Z_APPLICATION_H_
#define _Z_APPLICATION_H_

#include <vector>
#include <string>

namespace zi
{
    class ZApplication
    {
    public:
        ZApplication(int argc, char *argv[]);
        ~ZApplication(void);
        
    private:
        std::vector<std::string> m_args;
    };
}

#endif // _Z_APPLICATION_H_
