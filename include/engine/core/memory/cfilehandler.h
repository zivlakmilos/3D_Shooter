#ifndef _ENGINE_CORE_MEMORY_C_FILE_HANDLER_H_
#define _ENGINE_CORE_MEMORY_C_FILE_HANDLER_H_

#include <cstdio>

namespace zi
{
    class CFileHandler
    {
    public:
        CFileHandler(FILE *fd) { m_fd = fd; };
        virtual ~CFileHandler(void) { fclose(m_fd); };
        
    protected:
        FILE *m_fd;
    };
}

#endif // _ENGINE_CORE_MEMORY_C_FILE_HANDLER_H_
