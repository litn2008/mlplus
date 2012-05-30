#ifndef MLPLUS_DATASET_H
#define MLPLUS_DATASET_H
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <string>
#include <memory>
#include "attribute.h"
#include "instance_interface.h"
#include "instance_container_interface.h"
#include "attribute_container_interface.h"
namespace mlplus
{
using namespace std;
class Instance;
class DataSet
{
private:
    string mName;
    IAttributeContainer* mAttributes;
    IInstanceContainer* mInstances;
    int mTagetIndex;
    DataSet(const DataSet& other);
public:
    DataSet(const string& name, IAttributeContainer* attrCons, IInstanceContainer* insCons);
    DataSet(const string& name, IAttributeContainer* attrCons);
    DataSet(const string& name, IInstanceContainer* insCons);
    DataSet(const string& name);
    virtual ~DataSet();
    inline IInstanceContainer* getInstanceContainer();
    inline IAttributeContainer* getAttributeContainer();
    inline void getInstanceContainer(IInstanceContainer*);
    inline void getAttributeContainer(IAttributeContainer*);

    inline IAttributeIterator* newAttributeIterator();
    inline IInstanceIterator* newInstanceIterator();

    inline Attribute* attributeAt(int i);
    inline bool setAttribute(unsigned int i, Attribute* attr);
    inline Attribute* targetAttribute();
    inline int targetIndex() const;
    inline void setTargetIndex(int targetIndex);
    inline void setTarget(Attribute* attr);
    inline IInstance* instanceAt(int i);
    inline int numInstances();
    inline int numTargets();
    inline int numAttributes();
    inline void add(IInstance* instance);
    inline std::vector<ValueType> attributeArray(Attribute& attr);
    std::vector<ValueType> attributeArray(int attIndex);
#if 0
    bool checkForAttributeType(int attType) const;
    bool isStringAttributes() const
    {
        return checkForAttributeType(Attribute::STRING);
    }
    void deleteWithMissing(Attribute * attr)
    {
        deleteWithMissing(attr->index());
    }
    void deleteWithMissingTarget()
    {
        if(mTagetIndex < 0)
            throw new runtime_error("target index is not set");
        deleteWithMissing(mTagetIndex);
    }
    void randomize()
    {
        for(int j = numInstances() - 1; j > 0; j--)
            swap(j, (int)(random() % (j + 1)));
    }
    bool checkInstance(Instance& instance);
    void deleteAll();
    void deleteInstance(int index);
    void deleteAttributeAt(int position);
    void deleteWithMissing(int attIndex);
    DataSet* resample();
    DataSet* resampleWithWeights();
    DataSet* resampleWithWeights(vector<double>& weights);
    void swap(int i, int j);
private:
    /*
     * move all instances with missing values to end
     * @return the position point to the last instance without missing value
     */
    int moveInstanceWithMissing();
#endif
};

inline Attribute* DataSet::attributeAt(int i)
{
    assert(mAttributes);
    return mAttributes->at(i);
}
inline IInstanceContainer* DataSet::getInstanceContainer()
{
    return mInstances;
}
inline IAttributeContainer* DataSet::getAttributeContainer()
{
    return mAttributes;
}

inline void DataSet::getInstanceContainer(IInstanceContainer* cons)
{
    if (NULL != mInstances)
    {
        delete mInstances;
    }
    mInstances = cons;
}
inline void DataSet::getAttributeContainer(IAttributeContainer* cons)
{
    if (NULL != mAttributes)
    {
        delete mAttributes;
    }
    mAttributes = cons;
}
inline IAttributeIterator* DataSet::newAttributeIterator()
{
    return mAttributes->newIterator();
}
inline IInstanceIterator* DataSet::newInstanceIterator()
{
    return mInstances->newIterator();
}
inline IInstance* DataSet::instanceAt(int i)
{
    assert(mInstances);
    return mInstances->at(i);
}
inline bool DataSet::setAttribute(unsigned int i, Attribute* attr)
{
    assert(mAttributes);
    return mAttributes->set(i, attr);
}
inline Attribute* DataSet::targetAttribute() 
{
    return attributeAt(mTagetIndex);
}
inline int DataSet::targetIndex() const
{
    return mTagetIndex;
}
inline int DataSet::numInstances() 
{
    assert(mInstances);
    return mInstances->size();
}
inline int DataSet::numTargets() 
{
    if(mTagetIndex < 0)
        throw runtime_error("target index is not set");
    if(!targetAttribute()->isNominal())
        return 1;
    return targetAttribute()->numValues();
}
inline void DataSet::setTarget(Attribute* attr)
{
    mTagetIndex = attr->getIndex();
}
inline int DataSet::numAttributes()
{
    assert(mAttributes);
    return mAttributes->size();
}
inline void DataSet::setTargetIndex(int targetIndex)
{
    if(targetIndex >= numAttributes())
        throw new runtime_error("invalid class index");
    mTagetIndex = targetIndex;
}
inline vector<ValueType> DataSet::attributeArray(Attribute& attr)
{
    return attributeArray(attr.getIndex());
}
inline void DataSet::add(IInstance* instance)
{
    mInstances->add(instance);
}
}
#endif /**/
