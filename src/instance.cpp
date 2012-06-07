#include <instance.h>
#include <stdexcept>
#include <vector>
namespace mlplus
{

DenseInstance::DenseInstance(int numAttributes): AbstractInstance(numAttributes)
{
}
DenseInstance::DenseInstance(const DenseInstance& instance): AbstractInstance(instance)
{
}
DenseInstance::DenseInstance(const vector<ValueType>& values, ValueType weight): AbstractInstance(values, weight)
{
}
DenseInstance* DenseInstance::clone()
{
    return new DenseInstance(*this);
}
bool DenseInstance::isSparse()
{
    return false;
}
int DenseInstance::attributeIndex(int localIdx)
{
    return localIdx;
}
ValueType DenseInstance::getValue(int attrIndex)
{
    return mAttrValues.at(attrIndex);
}
void  DenseInstance::setValue(int attrIndex, ValueType value)
{
    if (attrIndex < 0)
    {
        return;
    }
    if((unsigned)attrIndex >= mAttrValues.size())
    {
        mAttrValues.resize(attrIndex + 1, missingValue());
    }
    mAttrValues[attrIndex] = value;
}
////////////////////////////////////////////////////////////////////////////////////////
//sparse implement
////////////////////////////////////////////////////////////////////////////////////////
SparseInstance::SparseInstance(int numAttributes):
    AbstractInstance(numAttributes), mIndices(numAttributes, -1)
{
    initGlobal2LocalMap();
}
SparseInstance::SparseInstance(const SparseInstance& instance):
    AbstractInstance(instance), mIndices(instance.mIndices)
{
    initGlobal2LocalMap();
}
SparseInstance::SparseInstance(const vector<ValueType>& values, const vector<int>& indices, ValueType weight):
    AbstractInstance(values, weight), mIndices(indices)
{
    initGlobal2LocalMap();
}
void SparseInstance::initGlobal2LocalMap()
{
    mGlobal2Local.clear();
    for (int i = 0; i < (int)mIndices.size(); ++i)
    {
        mGlobal2Local[mIndices[i]] = i;
    }
}
SparseInstance*  SparseInstance::clone()
{
    return new SparseInstance(*this);
}
bool SparseInstance::isSparse()
{
    return true;
}

int  SparseInstance::attributeIndex(int localIdx)
{
    return mIndices[localIdx];
}
int  SparseInstance::findPosition(int globalIndex) const
{
     map<int,int>::const_iterator it = mGlobal2Local.find(globalIndex);
     if (it == mGlobal2Local.end())
     {
         return -1;
     }
     return it->second;
}
void SparseInstance::setValue(int attrIndex, ValueType value)
{
    int idc = findPosition(attrIndex);
    if (idc < 0)
    {
        mGlobal2Local[attrIndex] = mAttrValues.size();
        mAttrValues.push_back(value);
        mIndices.push_back(attrIndex);
    }
    else
    {
        mAttrValues[idc] = value;
    }
}
ValueType SparseInstance::getValue(int attrIndex)
{
    int idc = findPosition(attrIndex);
    if (idc < 0)
    {
        AbstractInstance::missingValue();
    }
    return mAttrValues[idc];
}
}
