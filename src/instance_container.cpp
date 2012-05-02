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
    return mContainer.mInnerContainer[mCurrent++];
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
            p->mInnerContainer[i] = mInnerContainer[i]->clone();
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
    mInnerContainer.push_back(pInstance);
}
bool  DenseInstanceContainer::set(int index, IInstance* attr)
{
    if ((unsigned)index > mInnerContainer.size())
    {
        return false;
    }
    IInstance*&  p = mInnerContainer[index];
    if (NULL != p)
    {
        delete p;
    }
    p = attr;
    return true;
}
IInstance*  DenseInstanceContainer::at(int index)
{
    if ((unsigned)index > mInnerContainer.size())
    {
        return NULL;
    }
    return mInnerContainer[index];
}
IInstance*  DenseInstanceContainer::first()
{
    if (mInnerContainer.empty())
    {
        return NULL;
    }
    return mInnerContainer[0];
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
