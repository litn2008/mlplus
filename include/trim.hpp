#ifndef MLPLUS_STRING_trim_H 
#define MLPLUS_STRING_trim_H 
/** 
 * @brief trim.hpp provide the trim function for string
 *
 * void trimLeftIf(string, Predicate);
 * void trimRightIf(string, Predicate);
 * void trimIf(string, Predicate);
 *
 * void trimLeft(string);
 * void trimRight(string);
 * void trim(string);
 *
 * void trimLeft(string, del);
 * void trimRight(string, del);
 * void trim(string, del);
 *
 ////////////////////////////////////////////////////////////////////////////////
 //
 // the following group of function trim the origin string and copy it to a destination string
 //
 //////////////////////////////////////////////////////////////
 
 * void trimLeftCopyToIf(source, destination, Predicate);
 * void trimRightCopyToIf(source, destination, Predicate);
 * void trimCopyToIf(source, dest, Predicate);
 *
 * void trimLeftCopyTo(source, dest);
 * void trimRightCopyTo(source, dest);
 * void trimCopyTo(source, dest);
 *
 * void trimLeftCopyTo(source, dest, del);
 * void trimRightCopyTo(source, dest, del);
 * void trimCopyTo(source, dest, del);
 * 
 //////////////////////////////////////////////////////////////
 //
 // the following group of function trim the origin string 
 // and return the trimed string
 //
 //////////////////////////////////////////////////////////////
 //
 * string trimLeftCopyIf(string, Predicate);
 * string trimRightCopyIf(string, Predicate);
 * string trimCopyIf(string, Predicate);
 *
 * string trimLeftCopy(string);
 * string trimRightCopy(string);
 * string trimCopy(string);
 *
 * string trimLeftCopy(string, del);
 * string trimRightCopy(string, del);
 * string trimCopy(string, del);
 */

#include <string>
#include <algorithm>
#include "string_types.hpp"

namespace mlplus
{

template<typename PredicateT>
inline void trimLeftIf(std::string& s, PredicateT pred = PredicateT())
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(pred)));
}

template<typename PredicateT>
inline void trimRightIf(std::string& s, PredicateT pred = PredicateT())
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(pred)).base(), s.end());
}

template<typename PredicateT>
inline void trimIf(std::string& s, PredicateT pred = PredicateT())
{
    trimLeftIf(s, pred);
    trimRightIf(s, pred);
}

inline void trimLeft(std::string& inputStr)
{
    trimLeftIf(inputStr, IsSpace());
}

inline void trimRight(std::string& inputStr)
{
    trimRightIf(inputStr, IsSpace());
}

inline void trim(std::string& inputStr)
{
    trimIf(inputStr, IsSpace());
}

inline void trimLeft(std::string& s, const std::string& delim)
{
    std::string::size_type pos = s.find_first_not_of(delim); 
    if (pos != std::string::npos)
    {
        s.erase(0, pos);
    }
    else
    {
        s.clear();
    }
}

inline void trimRight(std::string& s, const std::string& delim)
{
    std::string::size_type pos = s.find_last_not_of(delim); 
    if (pos != std::string::npos)
    {
        s.erase(pos + 1);
    }
    else
    {
        s.clear();
    }
}

inline void trim(std::string& s, const std::string& delim)
{
    trimRight(s, delim);
    if (!s.empty())
    {
        trimLeft(s, delim);
    }
}

////////////////////////////////////////////////////////////////////////////////
template<typename PredicateT>
inline void trimLeftCopyToIf(const std::string& s, std::string& dest, PredicateT pred = PredicateT())
{
    std::string::const_iterator begin = std::find_if(s.begin(), s.end(), std::not1(pred));
    dest.clear();
    std::copy(begin, s.end(), std::back_inserter<std::string>(dest));
}

template<typename PredicateT>
inline void trimRightCopyToIf(const std::string& s, std::string& dest, PredicateT pred = PredicateT())
{
    std::string::const_iterator end = std::find_if(s.rbegin(), s.rend(), std::not1(pred)).base();
    dest.clear();
    std::copy(s.begin(), end, std::back_inserter<std::string>(dest));
}

template<typename PredicateT>
inline void trimCopyToIf(const std::string& s, std::string& dest, PredicateT pred = PredicateT())
{
    std::string::const_iterator begin = std::find_if(s.begin(), s.end(), std::not1(pred));
    std::string::const_iterator end = std::find_if(s.rbegin(), s.rend(), std::not1(pred)).base();
    dest.clear();
    std::copy(begin, end, std::back_inserter<std::string>(dest));
}

inline void trimLeftCopyTo(const std::string& s, std::string& d)
{
    return trimLeftCopyToIf(s, d, IsSpace());
}

inline void trimRightCopyTo(const std::string& s, std::string& d)
{
    return trimRightCopyToIf(s, d, IsSpace());
}

inline void trimCopyTo(const std::string& s, std::string& d)
{
    return trimCopyToIf(s, d, IsSpace());
}

inline void trimLeftCopyTo(const std::string& s, std::string& d, const std::string& del)
{
    d.clear();
    std::string::size_type end = s.find_first_not_of(del);
    if (end != std::string::npos)
    {
        d = s.substr(end); 
    }
}

inline void trimRightCopyTo(const std::string& s, std::string& d, const std::string& del)
{
    d.clear();
    std::string::size_type end = s.find_last_not_of(del);
    if (end != std::string::npos)
    {
        d = s.substr(0, end + 1);
    }
}

inline void trimCopyTo(const std::string& s, std::string& d, const std::string& del)
{
    d.clear();
    std::string::size_type begin = s.find_first_not_of(del);
    if (begin != std::string::npos)
    {
        std::string::size_type end = s.find_last_not_of(del);
        if (end >= begin)
        {
            d =  s.substr(begin, end - begin + 1);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
template<typename PredicateT>
inline std::string trimLeftCopyIf(const std::string& s, PredicateT pred = PredicateT())
{
    std::string outPut;
    trimLeftCopyToIf(s, outPut, pred);
    return outPut;
}

template<typename PredicateT>
inline std::string trimRightCopyIf(const std::string& s, PredicateT pred = PredicateT())
{
    std::string outPut;
    trimRightCopyToIf(s, outPut, pred);
    return outPut;
}

template<typename PredicateT>
inline std::string trimCopyIf(const std::string& s, PredicateT pred = PredicateT())
{
    std::string outPut;
    trimCopyToIf(s, outPut, pred);
    return outPut;
}

inline std::string trimLeftCopy(const std::string& s)
{
    return trimLeftCopyIf(s, IsSpace());
}

inline std::string trimRightCopy(const std::string& s)
{
    return trimRightCopyIf(s, IsSpace());
}

inline std::string trimCopy(const std::string& s)
{
    return trimCopyIf(s, IsSpace());
}

inline std::string trimLeftCopy(const std::string& s, const std::string& del)
{
    std::string result;
    trimLeftCopyTo(s, result, del);
    return result; 
}

inline std::string trimRightCopy(const std::string& s, const std::string& del)
{
    std::string result;
    trimRightCopyTo(s, result, del);
    return result; 
}

inline std::string trimCopy(const std::string& s, const std::string& del)
{
    std::string result;
    trimCopyTo(s, result, del);
    return result;
}


}//end of namespace 
#endif
