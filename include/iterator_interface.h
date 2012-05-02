#ifndef MLPLUS_ITERATOR_INTERFACE_H
#define MLPLUS_ITERATOR_INTERFACE_H
#include <memory>
#include <stdexcept>
namespace mlplus
{
class Attribute;
class IInstance;
class IAttributeIterator
{
public:
    virtual bool hasMore() const = 0;
    virtual void  reset() 
    {
        throw std::runtime_error("method not implemented!");
    }
    virtual Attribute* next() = 0;
    virtual ~IAttributeIterator(){};
};

class IInstanceIterator
{
public:
    virtual bool hasMore() const = 0;
    virtual void  reset() 
    {
        throw std::runtime_error("method not implemented!");
    }
    virtual IInstance* next() = 0;
    virtual ~IInstanceIterator(){};
};
typedef std::auto_ptr<IAttributeIterator> AutoAttributeIteratorPtr;
typedef std::auto_ptr<IInstanceIterator> AutoInstanceIteratorPtr;
}
#endif
