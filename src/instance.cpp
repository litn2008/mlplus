#include <instance.h>
#include <stdexcept>
#include <vector>

namespace mlplus
{

using namespace std;
Instance::Instance(int numAttributes):
    IInstance(),
    mDataset(NULL), mWeight(1), mGroupId(-1),
    mAttrValues(numAttributes, missingValue())
{
}

Instance::Instance(const Instance* instance) :
    IInstance(*instance),
    mDataset(instance->mDataset),
    mWeight(instance->mWeight),
    mGroupId(instance->mGroupId),
    mAttrValues(instance->mAttrValues)
{
}

Instance::Instance(const Instance& instance) :
    IInstance(instance),
    mDataset(instance.mDataset),
    mWeight(instance.mWeight),
    mGroupId(instance.mGroupId),
    mAttrValues(instance.mAttrValues)
{
}

Instance::Instance(const vector<DataType>& values, DataType weight):
    mDataset(NULL),
    mWeight(weight),
    mGroupId(-1), mAttrValues(values)
{
}

Instance::~Instance()
{
}
bool Instance::isSparse()
{
    return false;
}
int Instance::locate(int index) const
{
    return index;
}
int Instance::getGroupId() const
{
    return mGroupId;
}
void Instance::setGroupId(int id)
{
    mGroupId = id;
}
void Instance::reserve(int numAttribue)
{
    mAttrValues.reserve(numAttribue);
}
Attribute* Instance::attributeAt(int index)
{
    assert(mDataset != NULL);
    return mDataset->attributeAt(index);
}
Attribute*  Instance::targetAttribute()
{
    assert(mDataset != NULL);
    return mDataset->targetAttribute();
}
int  Instance::targetIndex()
{
    assert(mDataset != NULL);
    return mDataset->targetIndex();
}
bool  Instance::targetIsMissing()
{
    assert(targetIndex() >= 0);
    return isMissing(targetIndex());
}
DataType Instance::targetValue()
{
    assert(targetIndex() >= 0);
    return mAttrValues[targetIndex()];
}

DataSet* Instance::getDataset()
{
    return mDataset;
}

bool  Instance::hasMissingValue()
{
    assert(NULL == mDataset);
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


int Instance::numAttributes()
{
    return mAttrValues.size();
}
int Instance::numTargets()
{
    assert(mDataset);
    return mDataset->numTargets();
}
int Instance::numValues()
{
    return mAttrValues.size();
}
void Instance::replaceMissingValues(DataType value)
{
    for(unsigned int i = 0; i < mAttrValues.size(); i++)
        if(isMissingValue(mAttrValues[i]))
            mAttrValues[i] = value;
}
void Instance::setTargetMissing()
{
    if(targetIndex() < 0)
        throw runtime_error("class is not set");
    setMissing(targetIndex());
}
void Instance::setTargetValue(DataType value)
{
    if(targetIndex() < 0)
        throw runtime_error("class is not set");
    setValue(targetIndex(), value);
}
void Instance::setTargetValue(const string& value)
{
    if(targetIndex() < 0)
        throw runtime_error("class is not set");
    setValue(targetIndex(), value);
}

void Instance::setDataset(DataSet* instances)
{
    mDataset = instances;
}

bool Instance::isMissing(int attrIndex)
{
    int pos = locate(attrIndex);
    return mAttrValues.at(pos) == missingValue();
}
bool Instance::isMissing(Attribute& attr)
{
    return isMissing(attr.getIndex());
}
void Instance::setMissing(int attrIndex)
{
    setValue(attrIndex, missingValue());
}
void Instance::setMissing(Attribute& attr)
{
    setMissing(attr.getIndex());
}

void Instance::setValue(Attribute& attr, DataType value)
{
    setValue(attr.getIndex(), value);
}
void Instance::setWeight(double weight)
{
    mWeight = weight;
}

DataType Instance::getValue(int attrIndex)
{
    int position = locate(attrIndex);
    return mAttrValues.at(position);
}

DataType Instance::getValue(Attribute& attr)
{
    return getValue(attr.getIndex());
}

DataType Instance::getValue(Attribute * attr)
{
    return getValue(attr->getIndex());
}

double Instance::getWeight()
{
    return mWeight;
}

void Instance::setValue(int attrIndex, DataType value)
{
    int position = locate(attrIndex);
    if((int)mAttrValues.size() < attrIndex)
    {
        mAttrValues.resize(position + 1, missingValue());
    }
    mAttrValues[position] = value;
}

void Instance::setValue(int attrIndex, const string& value)
{
    assert(mDataset != NULL);
    Attribute* attr = attributeAt(attrIndex);
    setValue(*attr, value);
}

void Instance::setValue(Attribute& attr, const string& value)
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
    setValue(attr.getIndex(), (DataType)valIndex);
}
}
