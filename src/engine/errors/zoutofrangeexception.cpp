#include "engine/errors/exceptions.h"

zi::ZOutOfRangeException::ZOutOfRangeException(void)
    : ZException("Index out of range")
{
}

zi::ZOutOfRangeException::~ZOutOfRangeException(void)
{
}
