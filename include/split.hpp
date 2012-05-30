#ifndef MLPLUS_STRING_SPLIT_H
#define MLPLUS_STRING_SPLIT_H
#include <iostream>
#include <vector>
#include <string>
#include "string_types.hpp"
namespace mlplus
{
/* split a string by every characters in delimiter to a vector with  a filter
 *
 * @param str The input string
 * @param delimiter The Delimiter string each chararcter of which is a seperator
 *  eg. "\t\1\2", "\t","\1" and "\2" all are seperators
 * @param fitler The string Fitler
 *
 * @return the result vector<string>
 */
template<typename Filter>
void split(const std::string& str,  std::vector<std::string>& result, const std::string& delimiter, Filter filter)
{
    result.clear();
    result.reserve(str.size());
    std::string::size_type start = 0;
    std::string part;
    while (true)
    {
        std::string::size_type end = str.find_first_of(delimiter, start);
        if (end == std::string::npos)          //point to end
        {
            part = str.substr(start);
        }
        else
        {
            part = str.substr(start, end - start);
        }
        if (!filter(part))
        {
            result.push_back(part);
        }
        if (end == std::string::npos)
        {
            break;
        }
        start = end + 1;
    }
}

void split(const std::string& str, std::vector<std::string>& result, const std::string& delimiter=" \t\v")
{
    split(str, result, delimiter, blankString); 
}

}
#endif
