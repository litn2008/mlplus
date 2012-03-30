#include <attribute.h>
#include <string>
#include <stdexcept>
#include <cmath>

#ifndef NAN
# define NAN		builtinnan("")
#endif
#ifndef INFINITY
# define INFINITY	builtininf()
#endif

namespace mlplus
{

using namespace std;
const static  int RESERVED_VALUE_COUNT = 125;
Attribute::Attribute(const string& attrName, Attribute::AttributeType type) :
    mName(attrName), mIndex(-1), mType(type),mWeight(0.0)
{
}

Attribute::Attribute(const std::string& attrName, 
                     std::vector<std::string>& values,Attribute::AttributeType type):
    mName(attrName), mValues(values), mIndex(-1), mType(type), mWeight(0.0)
{
    if(mType == STRING ||  mType == NOMINAL)
    {
        mapValue2Index();
    }
}
Attribute::~Attribute()
{
}

void  Attribute::mapValue2Index()
{
    for (unsigned int i = 0; i < mValues.size(); ++i)
    {
        mValue2Index[mValues[i]] = i;
    }
}
int  Attribute::indexOfValue(const string& value) const
{
    std::map<std::string, int>::const_iterator it = mValue2Index.find(value);
    if (it != mValue2Index.end())
    {
        return it->second;
    }
    return -1;
}
bool Attribute::isRange(const string&  s) const
{
    const char* p = s.c_str();
    while(*p != 0)
    {
        //check All
        if((*p == 'A') && (*(p + 1) == 'l') && (*(p + 2) == 'l'))
        {
            return true;
        }
        //chek None
        if((*p == 'N') && (*(p + 1) == 'o') && (*(p + 2) == 'n') &&
                (*(p + 3) == 'e'))
        {
            return false;
        }
        if((*p == '(') || (*p == '['))
        {
            p++;
            while(*p != 0)
            {
                if(!strchr("+-.eEinf0123456789", *p))
                    return false;
                p++;
                if((*p == ')') || (*p == ']'))
                    return true;
            }
        }
        p++;
    }
    return false;
}
/*
void Attribute::makeRange(const string& s)
{
    const char * p = s.cstr();
    char buf[40];
    int i = 0;

    while(*p != 0)
    {
        if((*p == 'A') && (*(p + 1) == 'l') && (*(p + 2) == 'l'))
        {
            mRange.lowerBoundIsOpen = true;
            mRange.lowerBound = -INFINITY;
            mRange.upperBoundIsOpen = true;
            mRange.upperBound = INFINITY;
            return;
        }
        if((*p == 'N') && (*(p + 1) == 'o') && (*(p + 2) == 'n') &&
                (*(p + 3) == 'e'))
        {
            mRange.lowerBoundIsOpen = true;
            mRange.lowerBound = NAN;
            mRange.upperBoundIsOpen = true;
            mRange.upperBound = NAN;
            return;
        }
        if((*p == '(') || (*p == '['))
            break;
        p++;
    }
    if(*p == 0)
        goto error;
    mLowerBoundIsOpen = (*p == '(');

    p++;
    if(*p == 0)
        goto error;

    i = 0;
    buf[i++] = *p++;
    while((*p != 0) && (*p != '-') && (i < 40))
        buf[i++] = *p++;
    if(i == 40)
        goto error;
    if(*p != '-')
        goto error;
    buf[i] = 0;
    if(!strcmp(buf, "-inf"))
    {
        mLowerBound = -INFINITY;
    }
    else if(!strcmp(buf, "+inf") || !strcmp(buf, "inf"))
    {
        mLowerBound = INFINITY;
    }
    else
    {
        double d;
        if(sscanf(buf, "%lf", &d) != 1)
            goto error;
        mLowerBound = d;
    }

    p++;
    if(*p == 0)
        goto error;

    i = 0;
    buf[i++] = *p++;
    while((*p != 0) && (*p != ')') && (*p != ']') && (i < 40))
        buf[i++] = *p++;
    if(i == 40)
        goto error;
    if(*p == 0)
        goto error;
    buf[i] = 0;
    mUpperBoundIsOpen = (*p == ')');
    if(!strcmp(buf, "-inf"))
    {
        mUpperBound = -INFINITY;
    }
    else if(!strcmp(buf, "+inf") || !strcmp(buf, "inf"))
    {
        mUpperBound = INFINITY;
    }
    else
    {
        double d;
        if(sscanf(buf, "%lf", &d) != 1)
            goto error;
        mUpperBound = d;
    }

    return;

error:
    throw new runtimeerror("invalid range");
}
*/

bool Attribute::isInRange(double value) const
{
    if (!isNumeric())
    { 
        int v = (int)value;
        return (v >= 0 && v < (int)mValue2Index.size());
    }
    else
    {
        if(getLowerBound() == NAN || getUpperBound() == NAN)
            return false;
        if(lowerBoundIsOpen())
        {
            if(value <= getLowerBound())
                return false;
        }
        else
        {
            if(value < getLowerBound())
                return false;
        }
        if(upperBoundIsOpen())
        {
            if(value >= getUpperBound())
                return false;
        }
        else
        {
            if(value > getUpperBound())
                return false;
        }
    }
    return true;
}

string Attribute::toString() const
{
    string str = mName + " type:";
    switch (mType)
    {
    case NUMERIC:
        str += "NUMERIC";
        break;
    case STRING:
        str += "STRING";
        break;
    case NOMINAL:
        str += "NOMINAL";
        break;
    case DATE:
        str += "DATE";
        break;
    default: 
        str += "UNKNOW";
        break;
    }
    return str;
}

}

