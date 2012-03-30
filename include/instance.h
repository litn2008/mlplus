#ifndef MLPLUS_INSTANCE_H
#define MLPLUS_INSTANCE_H
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <vector>
#include <string>
#include <limits>
#include "attribute.h"
#include "dataset.h"
#include "instance_interface.h"
namespace mlplus
{
using namespace std;
class Instance: IInstance
{
private:
    DataSet* mDataset;
    double mWeight;
    int mGroupId;
    vector<DataType> mAttrValues;
protected:
    Instance() {}

public:
    Instance(int numAttributes);
    Instance(const Instance* instance);
    Instance(const Instance& instance);
    Instance(const vector<DataType>& values, DataType weight);
    virtual ~Instance();
    static DataType missingValue()
    {
        return std::numeric_limits<DataType>::quiet_NaN();
    }
    static bool isMissingValue(DataType val) 
    {
        return (val != val);
    }
    virtual bool isSparse();
    virtual int locate(int index) const;
    virtual int  getGroupId() const;
    virtual void setGroupId(int id);
    virtual void reserve(int numAttribue);
    virtual Attribute* attributeAt(int position);
    virtual Attribute* targetAttribute();
    virtual int targetIndex();
    virtual bool targetIsMissing();
    virtual DataType targetValue();

    virtual DataSet* getDataset(void);
    virtual void setDataset(DataSet* instances);

    virtual int numAttributes();
    virtual int numTargets();
    virtual int numValues();
    virtual void replaceMissingValues(DataType value);
    virtual void setTargetMissing();
    virtual void setTargetValue(DataType value);
    virtual void setTargetValue(const string& value);

    virtual bool hasMissingValue();
    virtual void setMissing(int attrIndex);
    virtual void setMissing(Attribute& attr);
    virtual bool isMissing(int attrIndex);
    virtual bool isMissing(Attribute& attr);
    virtual void setWeight(double weight);
    virtual double getWeight();

    virtual DataType getValue(int attrIndex);
    virtual DataType getValue(Attribute& attr);
    virtual DataType getValue(Attribute* attr);

    virtual void setValue(Attribute& attr, DataType value);
    virtual void setValue(int attrIndex, DataType value);
    virtual void setValue(int attrIndex, const string& value);
    virtual void setValue(Attribute& attr, const string& value);
};

}

#endif
