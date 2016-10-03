#ifndef _ENGINE_CORE_BASE_C_RESOURCE_HANDLER_H_
#define _ENGINE_CORE_BASE_C_RESOURCE_HANDLER_H_

#include <cstdlib>

namespace zi
{
    class BaseCResourceHandler
    {
    public:
        BaseCResourceHandler(void *pResourece) : m_pResourece(pResourece) {};
        virtual ~BaseCResourceHandler(void) { if(m_pResourece) free(m_pResourece); };
        
    protected:
        void *m_pResourece;
    };
}

#endif // _ENGINE_CORE_BASE_C_RESOURCE_HANDLER_H_
