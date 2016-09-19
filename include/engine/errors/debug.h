#ifndef _ENGINE_ERRORS_DEBUG_H_
#define _ENGINE_ERRORS_DEBUG_H_

/*
 * 1 - enable debug
 * 2 - disable debug
 */
#define _DEBUG_ENABLE_ 1

#include <iostream>

namespace zi
{
    class Debug
    {
    public:
        static void init(void);
        
        static void setDebugEnabled(bool debug);
        static bool isDebugEnabled(void);
        
        struct OutError
        {
            template<typename T>
            OutError &operator<<(const T &value)
            {
#if _DEBUG_ENABLE_ > 0
                if(s_debugEnabled)
                {
                    std::cout << "[Error]: " << value << std::endl;
                }
#endif // _DEBUG_ENABLE_
                return *this;
            };
        };
        
        struct OutWarning
        {
            template<typename T>
            OutWarning &operator<<(const T &value)
            {
#if _DEBUG_ENABLE_ > 0
                if(s_debugEnabled)
                {
                    std::cout << "[Warning]: " << value << std::endl;
                }
#endif // _DEBUG_ENABLE_
                return *this;
            };
        };
        
        struct OutDebug
        {
            template<typename T>
            OutDebug &operator<<(const T &value)
            {
#if _DEBUG_ENABLE_ > 0
                if(s_debugEnabled)
                {
                    std::cout << "[Debug]: " << value << std::endl;
                }
#endif // _DEBUG_ENABLE_
                return *this;
            };
        };
        
        static OutError error;
        static OutWarning warning;
        static OutDebug debug;
        
    private:
        static bool s_debugEnabled;
    };
}

#endif // _ENGINE_ERRORS_DEBUG_H_
