#ifndef  MLPLUS_DEBUG_H
#define MLPLUS_DEBUG_H

#include <cstdio>
#include <iostream>

namespace mlplus
{

using namespace std;

class Debug
{
    istream* mfStream;
    ostream * mOstream;

public:
    Debug(): mfStream(NULL), mOstream(NULL)
    {
    }
    void setStream(ostream * os);
    void setStream(istream* fp);
    void dprintf(const char * fmt, ...);
};
extern Debug Debug;
}

#endif
