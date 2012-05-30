#include <stdexcept>
#include <vector>
#include "dataset.h"
#include "attribute_container.h"
#include "attribute_value.h"
#include "instance_container.h"
namespace mlplus
{

DataSet::DataSet(const string& name, IAttributeContainer* attrCons, IInstanceContainer* insCons):
    mName(name), mAttributes(attrCons), mInstances(insCons), mTagetIndex(-1)
{
}
DataSet::DataSet(const string& name, IAttributeContainer* attrCons):
    mName(name), mAttributes(attrCons), mInstances(new DenseInstanceContainer), mTagetIndex(-1)
{
}
DataSet::DataSet(const string& name, IInstanceContainer* insCons):
    mName(name), mAttributes(new VectorAttributeContainer), mInstances(insCons), mTagetIndex(-1)
{
}
DataSet::DataSet(const string& name):
    mName(name), mAttributes(new VectorAttributeContainer), mInstances(new DenseInstanceContainer), mTagetIndex(-1)
{
}

DataSet::~DataSet()
{
    if (NULL != mAttributes)
    {
        delete mAttributes;
    }
    if (NULL != mInstances)
    {
        delete mInstances;
    }
}
vector<ValueType> DataSet::attributeArray(int index)
{
    vector <ValueType> v;
    v.reserve(numInstances());
    std::auto_ptr<IInstanceIterator> it(newInstanceIterator());
    while(it->hasMore())
    {
        IInstance* ins = it->next();
        if (NULL != ins)
        {
            ValueType val = ins->getValue(index);
            if (AttributeValue::isMissingValue(val))
            {
                v.push_back(val);
            }
        }
    }
    return v;
}

}
