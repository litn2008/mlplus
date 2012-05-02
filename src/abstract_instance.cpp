#include "abstract_instance.h"
#include <stdexcept>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <vector>
#include "attribute_value.h"
#include "dataset.h"
namespace mlplus
{
using namespace std;

ValueType AbstractInstance::missingValue()
{
    return AttributeValue::missingValue<ValueType>();
}
bool AbstractInstance::isMissingValue(ValueType v)
{
    return AttributeValue::isMissingValue(v);
}
AbstractInstance::AbstractInstance(int numAttributes):
    IInstance(),
    mDataset(NULL), mWeight(1), mGroupId(-1),
    mAttrValues(numAttributes, AttributeValue::missingValue<ValueType>())
{
}

AbstractInstance::AbstractInstance(const AbstractInstance* AbstractInstance):
    IInstance(*AbstractInstance),
    mDataset(AbstractInstance->mDataset),
    mWeight(AbstractInstance->mWeight),
    mGroupId(AbstractInstance->mGroupId),
    mAttrValues(AbstractInstance->mAttrValues)
{
}

AbstractInstance::AbstractInstance(const AbstractInstance& AbstractInstance) :
    IInstance(AbstractInstance),
    mDataset(AbstractInstance.mDataset),
    mWeight(AbstractInstance.mWeight),
    mGroupId(AbstractInstance.mGroupId),
    mAttrValues(AbstractInstance.mAttrValues)
{
}

AbstractInstance::AbstractInstance(const vector<ValueType>& values, ValueType weight):
    mDataset(NULL),
    mWeight(weight),
    mGroupId(-1), mAttrValues(values)
{
}
AbstractInstance::~AbstractInstance()
{
}
int AbstractInstance::getGroupId() const
{
    return mGroupId;
}
void AbstractInstance::setGroupId(int id)
{
    mGroupId = id;
}
void AbstractInstance::reserve(int numAttribue)
{
    mAttrValues.reserve(numAttribue);
}
Attribute* AbstractInstance::attributeAt(int index)
{
    assert(mDataset != NULL);
    return mDataset->attributeAt(index);
}
Attribute*  AbstractInstance::targetAttribute()
{
    assert(mDataset != NULL);
    return mDataset->targetAttribute();
}
int  AbstractInstance::targetIndex()
{
    assert(mDataset != NULL);
    return mDataset->targetIndex();
}
bool  AbstractInstance::targetIsMissing()
{
    assert(targetIndex() >= 0);
    return isMissing(targetIndex());
}
ValueType AbstractInstance::targetValue()
{
    assert(targetIndex() >= 0);
    return getValue(targetIndex());
}
DataSet* AbstractInstance::getDataset()
{
    return mDataset;
}
bool  AbstractInstance::hasMissingValue()
{
    assert(NULL != mDataset);
    for(int i = 0; i < numAttributes(); i++)
    {
        if(i != targetIndex())
        {
            if(isMissing(i))
            {
                return true;
            }
        }
    }
    return false;
}

int AbstractInstance::numAttributes()
{
    return mAttrValues.size();
}
int AbstractInstance::numTargets()
{
    assert(mDataset);
    return mDataset->numTargets();
}
int AbstractInstance::numValues()
{
    return mAttrValues.size();
}
void AbstractInstance::replaceMissingValues(ValueType value)
{
    for(unsigned int i = 0; i < mAttrValues.size(); i++)
        if(AttributeValue::isMissingValue(mAttrValues[i]))
            mAttrValues[i] = value;
}
void AbstractInstance::setTargetMissing()
{
    if(targetIndex() < 0)
        throw runtime_error("class is not set");
    setMissing(targetIndex());
}
void AbstractInstance::setTargetValue(ValueType value)
{
    if(targetIndex() < 0)
        throw runtime_error("class is not set");
    setValue(targetIndex(), value);
}
void AbstractInstance::setTargetValue(const string& value)
{
    if(targetIndex() < 0)
        throw runtime_error("class is not set");
    setValue(targetIndex(), value);
}
const vector<ValueType>&  AbstractInstance::getValueArray() const
{
    return mAttrValues;
}
void AbstractInstance::setDataset(DataSet* instances)
{
    mDataset = instances;
}
bool AbstractInstance::isMissing(int attrIndex)
{
    return AttributeValue::isMissingValue(getValue(attrIndex));
}
bool AbstractInstance::isMissing(Attribute& attr)
{
    return isMissing(attr.getIndex());
}
void AbstractInstance::setMissing(int attrIndex)
{
    setValue(attrIndex, AttributeValue::missingValue<ValueType>());
}
void AbstractInstance::setMissing(Attribute& attr)
{
    setMissing(attr.getIndex());
}
void AbstractInstance::setWeight(double weight)
{
    mWeight = weight;
}
ValueType AbstractInstance::getValue(Attribute& attr)
{
    return getValue(attr.getIndex());
}

ValueType AbstractInstance::getValue(Attribute * attr)
{
    return getValue(attr->getIndex());
}

double AbstractInstance::getWeight()
{
    return mWeight;
}
void AbstractInstance::setValue(Attribute& attr, ValueType value)
{
    setValue(attr.getIndex(), value);
}
void AbstractInstance::setValue(int attrIndex, const string& value)
{
    assert(mDataset != NULL);
    Attribute* attr = attributeAt(attrIndex);
    setValue(*attr, value);
}
void AbstractInstance::setValue(Attribute& attr, const string& value)
{
    if(!attr.isNominal() && !attr.isString())
        throw runtime_error("attribute should be nominal or string");
    int valIndex = attr.indexOfValue(value);
    if(valIndex == -1)
    {
        if(attr.isNominal())
        {
            throw runtime_error("value not defined for given nominal attribute");
        }
        else
        {
            attr.addValue(value);
            valIndex = attr.indexOfValue(value);
        }
    }
    setValue(attr.getIndex(), (ValueType)valIndex);
}
}
