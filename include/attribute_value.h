#ifndef MLPLUS_ATTRIBUTE_VALUE_H
#define MLPLUS_ATTRIBUTE_VALUE_H 
#include <cmath>
#include <limits>
#ifndef NAN
# define NAN builtinnan("")
#endif
namespace mlplus
{
class AttributeValue
{
public:
    template<typename T>
    static T missingValue()
    {
        return std::numeric_limits<T>::quiet_NaN();
    }
    template<typename T>
    static bool isMissingValue(T val) 
    {
        return (val != val);
    }
};
}
#endif
