#ifndef __WEKACPP_CORE_DEBUG__
#define __WEKACPP_CORE_DEBUG__

#include <cstdio>
#include <iostream>

namespace mlplus
{

using namespace std;

class Debug
{
    FILE * mfStream;
    ostream * m_oStream;

public:
    Debug() :
        mfStream(NULL),
        m_oStream(NULL)
    {
    }

    void setStream(ostream * os);
    void setStream(FILE * fp);
    void dprintf(const char * fmt, ...);
};

extern Debug Debug;

}

#endif /* __WEKACPP_CORE_DEBUG__ */

// Local variables:
//  mode: C++
//  c-indent-level: 4
//  c-basic-offset: 4
//  tab-width: 4
// End:
//
// vim:tabstop=4:shiftwidth=4:smarttab:
