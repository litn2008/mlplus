#ifndef MLPLUS_ATTRIBUTE_CONTAINER_INTERFACE_H
#define MLPLUS_ATTRIBUTE_CONTAINER_INTERFACE_H
namespace mlplus
{
class IAttributeIterator;
class IAttributeContainer
{
public:
    IAttributeContainer(){}
    virtual ~IAttributeContainer() {}
    virtual void merge(IAttributeContainer* cons) = 0;
    virtual void set(int index, Attribute* att) = 0;
    virtual void add(Attribute* att) = 0;
    virtual Attribute* at(int index) = 0;
    virtual unsigned int size() = 0;
    virtual IAttributeIterator* newIterator() = 0;
    virtual IAttributeContainer* deepCopy() = 0;
    virtual IAttributeContainer* shallowCopy() = 0; 
};
}
#endif
