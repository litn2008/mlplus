#include <vector>
#include <stdexcept>
#include "attribute_container.h"
using namespace mlplus;
/*------------------------------------------------------------------------------ */

VectorAttributeContainer* VectorAttributeContainer::shallowCopy()
{
    return new VectorAttributeContainer(*this);
}
VectorAttributeContainer* VectorAttributeContainer::deepCopy()
{
    VectorAttributeContainer* p = new VectorAttributeContainer(*this);
    for(VectorContainer::iterator it = p->mAttributeVec.begin(); 
        it != p->mAttributeVec.end(); ++it)
    {
        if(*it)
        {
            (*it).reset((*it)->clone());
        }
    }
    return p;
}
VectorAttributeContainer::VectorAttributeContainer(VectorAttributeContainer::VectorContainer& cons):
    mAttributeVec(cons)
{
}
VectorAttributeContainer::VectorAttributeContainer(int attributeCapbility)
{
    if(attributeCapbility > 0)
    {
        mAttributeVec.reserve(attributeCapbility);
    }
    else
    {
        mAttributeVec.reserve(ATTRIBUTE_THREHOLD);
    }
}
void VectorAttributeContainer::merge(IAttributeContainer* vec)
{
    if(NULL == vec) return;
    AutoAttributeIteratorPtr p(vec->newIterator());
    while(p->hasMore())
    {
        mAttributeVec.push_back(SharedAttributePtr(p->next()));
    }
}
Attribute* VectorAttributeContainer::at(int index)
{
    if((unsigned)index < mAttributeVec.size())
    {
        return mAttributeVec[index].get();
    }
    return NULL;
}
bool VectorAttributeContainer::set(int index, Attribute* attr)
{
    if((unsigned)index >= mAttributeVec.size())
    {
        return false;
    }
    mAttributeVec[index].reset(attr);
    return true;
}
void VectorAttributeContainer::add(Attribute* att)
{
    mAttributeVec.push_back(SharedAttributePtr(att));
}
unsigned int VectorAttributeContainer::size()
{
    return mAttributeVec.size();
}
IAttributeIterator* VectorAttributeContainer::newIterator()
{
    return new VectorIterator(mAttributeVec);
}

/*------------------------------------------------------------------------------ */
MapAttributeContainer* MapAttributeContainer::shallowCopy()
{
    return new MapAttributeContainer(*this);
}
MapAttributeContainer* MapAttributeContainer::deepCopy()
{
    MapAttributeContainer* p = new MapAttributeContainer(*this);
    for(MapContainer::iterator it = p->mAttributeMap.begin(); 
        it != p->mAttributeMap.end(); ++it)
    {
        if(NULL != it->second)
        {
            it->second.reset(it->second->clone());
        }
    }
    return p;
}
MapAttributeContainer::MapAttributeContainer(MapContainer& mp):
    mAttributeMap(mp)
{
}
void MapAttributeContainer::merge(IAttributeContainer* cons)
{
    if (NULL == cons)
    {
        return;
    }
    AutoAttributeIteratorPtr p(cons->newIterator());
    while(p->hasMore())
    {
        add(p->next());
    }
}
Attribute*  MapAttributeContainer::at(int index)
{
    MapContainer::iterator it = mAttributeMap.find(index);
    if(it != mAttributeMap.end())
    {
        return it->second.get();
    }
    return NULL;
}
bool  MapAttributeContainer::set(int index, Attribute* att)
{
    MapContainer::iterator it = mAttributeMap.find(index);
    if(it ==  mAttributeMap.end())
    {
        return false;
    }
    it->second.reset(att);
    return true;
}
void  MapAttributeContainer::add(Attribute* att)
{
    unsigned count = mAttributeMap.size();
    mAttributeMap[count].reset(att);
}
unsigned int  MapAttributeContainer::size()
{
    return mAttributeMap.size();
}
IAttributeIterator* MapAttributeContainer::newIterator()
{
    return new MapIterator(mAttributeMap);
}
