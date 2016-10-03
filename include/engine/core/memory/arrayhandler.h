#ifndef _ENGINE_CORE_MEMORY_ARRAY_HANDLER_H_
#define _ENGINE_CORE_MEMORY_ARRAY_HANDLER_H_

#include "baseresourcehandler.h"

namespace zi
{
    template<typename T>
    class ArrayHandler : public BaseResourceHandler<T>
    {
    public:
        ArrayHandler(T *pResource) : BaseResourceHandler(pResource) {};
        virtual ~ArrayHandler(void) { delete[] m_pResource; };
    };
}

#endif // _ENGINE_CORE_MEMORY_ARRAY_HANDLER_H_
