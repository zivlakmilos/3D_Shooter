#ifndef _Z_EXCEPTIONS_H_
#define _Z_EXCEPTIONS_H_

#include <string>
#include <exception>

namespace zi
{
    class ZException : public std::exception
    {
    public:
        ZException(std::string what);
        ZException(void);
        virtual ~ZException();
        
        virtual const char *what() const throw();
        
    private:
        std::string m_what;
    };
}

#endif // _Z_EXCEPTIONS_H_
