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
int DenseInstance::getIndexAt(int localIdx)
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
}
SparseInstance::SparseInstance(const SparseInstance& instance):
    AbstractInstance(instance), mIndices(instance.mIndices)
{
}
SparseInstance::SparseInstance(const vector<ValueType>& values, const vector<int>& indices, ValueType weight):
    AbstractInstance(values, weight), mIndices(indices)
{
}
SparseInstance*  SparseInstance::clone()
{
    return new SparseInstance(*this);
}
bool SparseInstance::isSparse()
{
    return true;
}
int  SparseInstance::getIndexAt(int localIdx)
{
    return mIndices[localIdx];
}
int SparseInstance::findPosition(int globalIndex) const
{
    vector<int>::const_iterator it = find(mIndices.begin(), mIndices.end(), globalIndex);
    if(mIndices.end() != it)
    {
        return -1;
    }
    return it - mIndices.begin();
}
void SparseInstance::setValue(int attrIndex, ValueType value)
{
    int idc = findPosition(attrIndex);
    if (idc < 0)
    {
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
