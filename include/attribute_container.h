#ifndef MLPLUS_ATTRIBUTE_CONTAINER_H
#define MLPLUS_ATTRIBUTE_CONTAINER_H
#include <map>
#include <vector>
#include <stdexcept>
#include "attribute.h"
#include "iterator_interface.h"
#include "attribute_container_interface.h"
#include "ptr_define.h"
namespace mlplus
{
class VectorAttributeContainer: public IAttributeContainer
{
public:
    typedef std::vector<Attribute*>  VectorContainer;
    class VectorIterator: public IAttributeIterator
    {
    public:
        VectorContainer& mContainer;
        VectorContainer::iterator mCur;
        VectorIterator(VectorAttributeContainer::VectorContainer& cons): mContainer(cons), mCur(cons.begin()) {}
        /*override*/ void reset()
        {
            mCur = mContainer.begin();
        }
        /*override*/ bool hasMore() const
        {
            return mContainer.end() != mCur;
        }
        /*override*/ Attribute* next()
        {
            return *mCur++;
        }
    };
private:
    VectorContainer mAttributeVec;
    const static int  ATTRIBUTE_THREHOLD = 1024;
public:
    VectorAttributeContainer(int attributeCapbility = ATTRIBUTE_THREHOLD);
    VectorAttributeContainer(VectorAttributeContainer::VectorContainer& cons);
    /*override*/ void merge(IAttributeContainer* cons);
    /*override*/ bool set(int index, Attribute* att);
    /*override*/ void add(Attribute* att);
    /*override*/ Attribute* at(int index);
    /*override*/ unsigned int size();
    /*override*/ IAttributeIterator* newIterator();
    /*override*/ VectorAttributeContainer* shallowCopy();
    /*override*/ VectorAttributeContainer* deepCopy();
};
class MapAttributeContainer:public IAttributeContainer
{
public:
    typedef std::map<int, Attribute*>  MapContainer;
    class MapIterator: public IAttributeIterator
    {
    public:
        MapAttributeContainer::MapContainer& mContainer;
        MapAttributeContainer::MapContainer::iterator mCur;
        MapIterator(MapAttributeContainer::MapContainer& cons): mContainer(cons), mCur(cons.begin()) {}
        /*override*/void reset()
        {
            mCur = mContainer.begin();
        }
        /*override*/ bool hasMore() const
        {
            return mContainer.end() != mCur;
        }
        /*override*/ Attribute* next()
        {
            Attribute* i = mCur->second;
            ++mCur;
            return i;
        }
    };
public:
    MapAttributeContainer(MapContainer& mp);
    /*override*/ void merge(IAttributeContainer* cons);
    /*override*/ bool set(int index, Attribute* att);
    /*override*/ void add(Attribute* att);
    /*override*/ Attribute* at(int index);
    /*override*/ unsigned int size();
    /*override*/ IAttributeIterator* newIterator();
    /*override*/ MapAttributeContainer* shallowCopy();
    /*override*/ MapAttributeContainer* deepCopy();
private: 
   MapContainer mAttributeMap;
};
}
#endif

