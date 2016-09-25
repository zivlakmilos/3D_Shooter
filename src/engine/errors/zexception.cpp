#include "engine/errors/exceptions.h"

zi::ZException::ZException(void)
    : ZException("Unknow exception")
{
}

zi::ZException::ZException(std::string what, int code)
    : m_what(what),
      m_code(code)
{
}

zi::ZException::~ZException(void)
{
}

const char *zi::ZException::what(void) const throw()
{
    return m_what.c_str();
}

int zi::ZException::code(void) const throw()
{
    return m_code;
}

std::ostream &zi::operator<<(std::ostream &lhs, const zi::ZException &rhs)
{
    lhs << rhs.what();
    
    return lhs;
}
