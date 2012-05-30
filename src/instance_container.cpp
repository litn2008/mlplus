#include "instance_container.h"
#include "instance_interface.h"
using namespace mlplus;

DenseInstanceIterator::DenseInstanceIterator(DenseInstanceContainer& dit):
    mContainer(dit), mCurrent(0)
{
}
bool DenseInstanceIterator::hasMore() const
{
    return (unsigned)mCurrent < mContainer.size();
}
IInstance*  DenseInstanceIterator::next()
{
    return mContainer.mInnerContainer[mCurrent++].get();
}
void  DenseInstanceIterator::reset()
{
    mCurrent= 0;
}

/*--------------------------------------------------------------------------- */
DenseInstanceContainer::DenseInstanceContainer()
{
}
DenseInstanceContainer::~DenseInstanceContainer()
{
}
void DenseInstanceContainer::clear()
{
    mInnerContainer.clear();
}

DenseInstanceContainer::DenseInstanceContainer(const DenseInstanceContainer& other):
    IInstanceContainer(other), mInnerContainer(other.mInnerContainer)
{
    
}
DenseInstanceContainer*  DenseInstanceContainer::deepCopy()
{
    DenseInstanceContainer* p =  new DenseInstanceContainer(*this);
    for (unsigned i = 0; i < p->mInnerContainer.size(); ++i)
    {
        if (p->mInnerContainer[i])
        {
            p->mInnerContainer[i].reset(mInnerContainer[i]->clone());
        }
    }
    return p;
}
unsigned  DenseInstanceContainer::size() const
{
    return mInnerContainer.size();
}
void DenseInstanceContainer::add(IInstance* pInstance)
{
    mInnerContainer.push_back(SharedInstancePtr(pInstance));
}
bool  DenseInstanceContainer::set(int index, IInstance* attr)
{
    if ((unsigned)index > mInnerContainer.size())
    {
        return false;
    }
    mInnerContainer[index].reset(attr);
    return true;
}
IInstance*  DenseInstanceContainer::at(int index)
{
    if ((unsigned)index > mInnerContainer.size())
    {
        return NULL;
    }
    return mInnerContainer[index].get();
}
IInstance*  DenseInstanceContainer::first()
{
    if (mInnerContainer.empty())
    {
        return NULL;
    }
    return mInnerContainer[0].get();
}
IInstance*  DenseInstanceContainer::next(int index)
{
    index++;
    return at(index);
}
IInstanceIterator*  DenseInstanceContainer::newIterator()
{
    return new DenseInstanceIterator(*this);
}
/*----------------------------------------------------------------------------*/

SparseInstanceIterator::SparseInstanceIterator(SparseInstanceContainer& dit):mContainer(dit), mCur(mContainer.mInnerContainer.begin())
{
}
/*override*/bool SparseInstanceIterator::hasMore() const
{
    return mCur != mContainer.mInnerContainer.end();
}
/*override*/void  SparseInstanceIterator::reset()
{
    mCur = mContainer.mInnerContainer.begin();
}
/*override*/IInstance* SparseInstanceIterator::next()
{
    IInstance* a = mCur->second.get();
    ++mCur;
    return a;
}
/*----------------------------------------------------------------------------*/
SparseInstanceContainer::SparseInstanceContainer()
{
}
SparseInstanceContainer::~SparseInstanceContainer()
{
}
void SparseInstanceContainer::clear()
{
    mInnerContainer.clear();
}
SparseInstanceContainer* SparseInstanceContainer::deepCopy()
{
    SparseInstanceContainer* other = new SparseInstanceContainer(*this);
    std::map<int, SharedInstancePtr>::iterator it = other->mInnerContainer.begin();
    for (; it != other->mInnerContainer.end(); ++it)
    {
        it->second.reset(it->second->clone());
    }
    return other;
}
unsigned  SparseInstanceContainer::size() const
{
    return mInnerContainer.size();
}
void  SparseInstanceContainer::add(IInstance* pInstance)
{
    int sz = size();
    mInnerContainer[sz].reset(pInstance);
}
bool  SparseInstanceContainer::set(int index, IInstance* pIns)
{
    if ((unsigned)index < mInnerContainer.size())
    {
        mInnerContainer[index].reset(pIns);
        return true;
    }
    return false;
}
IInstance*  SparseInstanceContainer::at(int index)
{
    return mInnerContainer[index].get();
}
IInstance*  SparseInstanceContainer::first()
{
    return mInnerContainer[0].get();
}
IInstance*  SparseInstanceContainer::next(int index)
{
    return mInnerContainer[++index].get();
}
IInstanceIterator*  SparseInstanceContainer::newIterator()
{
    return new SparseInstanceIterator(*this);
}
