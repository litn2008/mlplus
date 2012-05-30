#ifndef MLPLUS_INSTANCE_CONTAINER_H
#define MLPLUS_INSTANCE_CONTAINER_H
#include <vector>
#include "instance_container_interface.h"
#include "iterator_interface.h"
#include "ptr_define.h"
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
    std::vector<SharedInstancePtr> mInnerContainer;
    friend class DenseInstanceIterator;
};

class SparseInstanceContainer:public IInstanceContainer
{
public:
    typedef std::map<int, SharedInstancePtr> InnerType;
    SparseInstanceContainer();
    /*override*/ ~SparseInstanceContainer();
    /*override*/ void clear();
    /*override*/ SparseInstanceContainer* deepCopy();
    /*override*/ unsigned size() const;
    /*override*/ void add(IInstance* pInstance);
    /*override*/ bool set(int index, IInstance* attr);
    /*override*/ IInstance* at(int index);
    /*override*/ IInstance* first();
    /*override*/ IInstance* next(int index);
    /*override*/ IInstanceIterator* newIterator();
private:
    std::map<int, SharedInstancePtr> mInnerContainer;
    friend class SparseInstanceIterator;
};

class SparseInstanceIterator: public IInstanceIterator
{
public:
    SparseInstanceIterator(SparseInstanceContainer& dit);
    /*override*/bool hasMore() const;
    /*override*/void  reset();
    /*override*/IInstance* next();
private:
    SparseInstanceContainer& mContainer;
    std::map<int, SharedInstancePtr>::iterator mCur;
};
}
#endif
