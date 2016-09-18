#include "engine/errors/debug.h"

bool zi::Debug::s_debugEnabled;

zi::Debug::OutError zi::Debug::error;
zi::Debug::OutWarning zi::Debug::warning;
zi::Debug::OutDebug zi::Debug::debug;

void zi::Debug::init(void)
{
    s_debugEnabled = false;
}

bool zi::Debug::isDebugEnabled(void)
{
#if _DEBUG_ENABLED_ > 0
    return s_debugEnabled;
#endif // _DEBUG_ENABLED_ > 0
    return false;
}

void zi::Debug::setDebugEnabled(bool debug)
{
#if _DEBUG_ENABLED_ > 0
    s_debugEnabled = debug;
#endif // _DEBUG_ENABLED_ > 0
}
