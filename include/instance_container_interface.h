#ifndef MLPLUS_INSTANCE_CONTAINER_INTERFACE_H
#define MLPLUS_INSTANCE_CONTAINER_INTERFACE_H
namespace mlplus
{
class IInstance;
class IInstanceIterator;
class IInstanceContainer
{
public:
    IInstanceContainer(){}
    virtual ~IInstanceContainer(){}
    virtual void clear() = 0;
    virtual IInstanceContainer* deepCopy() = 0;
    virtual unsigned size() const = 0;
    virtual void add(IInstance* pInstance) = 0;
    virtual bool set(int index, IInstance* attr) = 0;
    virtual IInstance* at(int index) = 0;
    virtual IInstance* first() = 0;
    virtual IInstance* next(int index) = 0;
    virtual IInstanceIterator* newIterator() = 0;
    /*
       virtual bool compare(const InstanceContainer& Instances) const = 0;
       virtual bool setInstanceReader(InstanceReader* pReader) = 0;
       virtual InstanceReader* getInstanceReader() const = 0;
    */
};
}
#endif
