#include "engine/zexceptions.h"

using namespace std;

zi::ZException::ZException(std::string what)
    : exception(),
      m_what(what)
{
}

zi::ZException::ZException(void)
    : ZException("Undefined exception")
{
}

zi::ZException::~ZException()
{
}

const char *zi::ZException::what() const throw()
{
    return m_what.c_str();
}
