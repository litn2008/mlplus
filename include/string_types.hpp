#ifndef MLPLUS_STRING_TYPES_H
#define MLPLUS_STRING_TYPES_H
#include <functional>
#include <string>
namespace mlplus
{
struct IsSpace: public std::unary_function<char, bool>
{
    inline bool operator()(char ch) const
    {
        return std::isspace(ch);
    }
};

inline bool blankString(const std::string& str) 
{
    return str.find_first_not_of(" \t\n\v") == std::string::npos;
}

}
#endif
