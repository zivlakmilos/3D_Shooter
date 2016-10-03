#ifndef _ENGINE_CORE_BASE_RESOURCE_HANDLER_H_
#define _ENGINE_CORE_BASE_RESOURCE_HANDLER_H_

namespace zi
{
    template<typename T>
    class BaseResourceHandler
    {
    public:
        BaseResourceHandler(T *pResource) : m_pResource(pResource) {};
        virtual ~BaseResourceHandler(void) { delete m_pResource; };
        
    protected:
        T *m_pResource;
    };
}

#endif // _ENGINE_CORE_BASE_RESOURCE_HANDLER_H_
