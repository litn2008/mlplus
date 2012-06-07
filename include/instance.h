#ifndef MLPLUS_INSTANCE_H
#define MLPLUS_INSTANCE_H
#include <map>
#include <vector>
#include "abstract_instance.h"
namespace mlplus
{
class DenseInstance:public AbstractInstance
{
public:
    DenseInstance(int numAttributes);
    DenseInstance(const DenseInstance& instance);
    DenseInstance(const vector<ValueType>& values, ValueType weight = 1.0);
    DenseInstance*  clone();
    /*override*/ bool isSparse();
    using AbstractInstance::setValue;
    using AbstractInstance::getValue;
    /*override*/ void setValue(int attrIndex, ValueType value);
    /*override*/ ValueType getValue(int attrIndex);
    /*overirde*/ int attributeIndex(int localIdx);
};
class SparseInstance: public AbstractInstance
{
public:
    SparseInstance(int numAttributes);
    SparseInstance(const SparseInstance& instance);
    SparseInstance(const vector<ValueType>& values, const vector<int>& indices, ValueType weight);
    using AbstractInstance::setValue;
    using AbstractInstance::getValue;
    /*override*/SparseInstance*  clone();
    /*override*/bool isSparse();
    /*override*/void setValue(int attrIndex, ValueType value);
    /*override*/ValueType getValue(int attrIndex);
    /*overirde*/ int attributeIndex(int localIdx);
private:
    void initGlobal2LocalMap();
    int findPosition(int globalIndex) const;
    std::vector<int> mIndices;
    std::map<int,int> mGlobal2Local;
};
}

#endif
