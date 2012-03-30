#ifndef MLPLUS_INSTANCE_INTERFACE_H
#define MLPLUS_INSTANCE_INTERFACE_H
#include <string>
#include <iterator>
namespace mlplus
{
using namespace std;
typedef float DataType;
class Attribute;
class DataSet;

class IInstance
{
public:
    virtual ~IInstance() = 0;
    virtual bool isSparse() = 0;
    virtual int locate(int index) const = 0;
    virtual int  getGroupId() const = 0;
    virtual void setGroupId(int id) = 0;
    virtual void reserve(int numAttribue) = 0;
    virtual Attribute* attributeAt(int index) = 0;
    virtual Attribute* targetAttribute() = 0;
    virtual int targetIndex() = 0;
    virtual bool targetIsMissing() = 0;
    virtual DataType targetValue() = 0;

    virtual DataSet* getDataset(void) = 0;
    virtual void setDataset(DataSet* instances) = 0;

    virtual int numAttributes() = 0;
    virtual int numTargets() = 0;
    virtual int numValues() = 0;
    virtual void replaceMissingValues(DataType value) = 0;
    virtual void setTargetMissing() = 0;
    virtual void setTargetValue(DataType value) = 0;
    virtual void setTargetValue(const string& value) = 0;
    virtual bool hasMissingValue() = 0;

    virtual void setMissing(int attrIndex) = 0;
    virtual void setMissing(Attribute& attr) = 0;
    virtual bool isMissing(int attrIndex) = 0;
    virtual bool isMissing(Attribute& attr) = 0;

    virtual void setWeight(double weight) = 0;
    virtual double getWeight() = 0;

    virtual DataType getValue(int attrIndex) = 0;
    virtual DataType getValue(Attribute& attr) = 0;
    virtual DataType getValue(Attribute* attr) = 0;

    virtual void setValue(Attribute& attr, DataType value) = 0;
    virtual void setValue(int attrIndex, DataType value) = 0;
    virtual void setValue(int attrIndex, const string& value) = 0;
    virtual void setValue(Attribute& attr, const string& value) = 0;
};

inline IInstance::~IInstance() {}
}

#endif
