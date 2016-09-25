#ifndef _ENGINE_ERRORS_EXCEPTIONS_H_
#define _ENGINE_ERRORS_EXCEPTIONS_H_

#include <exception>
#include <string>
#include <ostream>

namespace zi
{
    /*
     * Base (basic) exception
     */
    class ZException : public std::exception
    {
    public:
        ZException(void);
        ZException(std::string what, int code = 0);
        virtual ~ZException(void);
        
        virtual const char *what(void) const throw();
        virtual int code(void) const throw();
        
    protected:
        std::string m_what;
        int m_code;
    };
    
    /*
     * Out of range exception
     */
    class ZOutOfRangeException : ZException
    {
    public:
        ZOutOfRangeException(void);
        virtual ~ZOutOfRangeException(void);
    };
    
    /*
     * Operators
     */
    std::ostream &operator<<(std::ostream &lhs, const ZException &rhs);
}

#endif // _ENGINE_ERRORS_EXCEPTIONS_H_
