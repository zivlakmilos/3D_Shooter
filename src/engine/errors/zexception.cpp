#include "engine/errors/exceptions.h"

zi::ZException::ZException(void)
    : ZException("Unknow exception")
{
}

zi::ZException::ZException(std::string what)
    : m_what(what)
{
}

zi::ZException::~ZException(void)
{
}

const char *zi::ZException::what(void) const throw()
{
    return m_what.c_str();
}

std::ostream &zi::operator<<(std::ostream &lhs, const zi::ZException &rhs)
{
    lhs << rhs.what();
    
    return lhs;
}
