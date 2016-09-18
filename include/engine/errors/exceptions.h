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
        ZException(std::string what);
        virtual ~ZException(void);
        
        virtual const char *what(void) const throw();
        
    protected:
        std::string m_what;
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
