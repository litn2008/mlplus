#ifndef MLPLUS_ABSTRACT_INSTANCE_H
#define MLPLUS_ABSTRACT_INSTANCE_H
#include <vector>
#include <string>
#include "instance_interface.h"
namespace mlplus
{
class DataSet;
class Attribute;
using namespace std;
class AbstractInstance:public IInstance
{
protected:
    DataSet* mDataset;
    double mWeight;
    int mGroupId;
    vector<ValueType> mAttrValues;
protected:
    AbstractInstance() {}
public:
    static ValueType missingValue();
    static bool isMissingValue(ValueType v);
    AbstractInstance(int numAttributes);
    AbstractInstance(const AbstractInstance* instance);
    AbstractInstance(const AbstractInstance& instance);
    AbstractInstance(const vector<ValueType>& values, ValueType weight);
    /*override*/ ~AbstractInstance();
    /*override*/ int  getGroupId() const;
    /*override*/ void setGroupId(int id);
    /*override*/ void reserve(int numAttribue);
    /*override*/ Attribute* attributeAt(int global);
    /*override*/ Attribute* targetAttribute();
    /*override*/ int targetIndex();
    /*override*/ bool targetIsMissing();
    /*override*/ ValueType targetValue();

    /*override*/ const vector<ValueType>&  getValueArray() const;
    /*override*/ DataSet* getDataset(void);
    /*override*/ void setDataset(DataSet* instances);

    /*override*/ int numAttributes();
    /*override*/ int numTargets();
    /*override*/ int numValues();
    /*override*/ void replaceMissingValues(ValueType value);
    /*override*/ void setTargetMissing();
    /*override*/ void setTargetValue(ValueType value);
    /*override*/ void setTargetValue(const string& value);

    /*override*/ bool hasMissingValue();
    /*override*/ void setMissing(int attrIndex);
    /*override*/ void setMissing(Attribute& attr);
    /*override*/ bool isMissing(int attrIndex);
    /*override*/ bool isMissing(Attribute& attr);
    /*override*/ void setWeight(double weight);
    /*override*/ double getWeight();

    /*override*/ ValueType getValue(Attribute& attr);
    /*override*/ ValueType getValue(Attribute* attr);
    /*override*/ ValueType getValue(int attrIndex) = 0;

    /*override*/ void setValue(Attribute& attr, ValueType value);
    /*override*/ void setValue(Attribute& attr, const string& value);
    /*override*/ void setValue(int attrIndex, const string& value);
    virtual void setValue(int attrIndex, ValueType value) = 0;
};
}

#endif
