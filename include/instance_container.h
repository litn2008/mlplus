#ifndef MLPLUS_INSTANCE_CONTAINER_H
#define MLPLUS_INSTANCE_CONTAINER_H
#include <vector>
#include "instance_container_interface.h"
#include "iterator_interface.h"
namespace mlplus
{
class DenseInstanceContainer;
class DenseInstanceIterator: public IInstanceIterator
{
public:
    DenseInstanceIterator(DenseInstanceContainer& dit);
    /*override*/bool hasMore() const;
    /*override*/void  reset();
    /*override*/IInstance* next();
private:
    DenseInstanceContainer& mContainer;
    int mCurrent;
};

class DenseInstanceContainer:public IInstanceContainer
{
private:
    DenseInstanceContainer(const DenseInstanceContainer&);
public:
    DenseInstanceContainer();
    /*override*/ ~DenseInstanceContainer();
    /*override*/ void clear();
    /*override*/  DenseInstanceContainer* deepCopy();
    /*override*/ unsigned size() const;
    /*override*/ void add(IInstance* pInstance);
    /*override*/ bool set(int index, IInstance* attr);
    /*override*/ IInstance* at(int index);
    /*override*/ IInstance* first();
    /*override*/ IInstance* next(int index);
    /*override*/ IInstanceIterator* newIterator();
private:
    std::vector<IInstance*> mInnerContainer;
    friend class DenseInstanceIterator;
};
#if 0
class SparseInstanceContainer:public IInstanceContainer
{
public:
    SparseInstanceContainer();
    /*override*/ ~SparseInstanceContainer();
    /*override*/ void clear();
    /*override*/ InstanceContainer* deepCopy();
    /*override*/ unsigned size();
    /*override*/ bool add(IInstance* pInstance);
    /*override*/ bool set(int index, Instance* attr);
    /*override*/ IInstance* at(int index);
    /*override*/ IInstance* first();
    /*override*/ IInstance* next(int index);
    /*override*/ IInstanceIterator* newIterator();
private:
    std::map<int, IInstance*> mInnerContainer;
}
#endif
}
#endif
