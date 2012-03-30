#ifndef MLPLUS_DATASET_H
#define MLPLUS_DATASET_H

#include <cstdlib>
#include <stdexcept>
#include <string>
#include "attribute.h"
namespace mlplus
{
using namespace std;
class Instance;
class DataSet
{
private:
    string mName;
    vector<Attribute*> mAttributes;
    vector<Instance*> mInstances;
    int mTagetIndex;
public:
    DataSet(const string& name, vector<Attribute*>& attrs, int capacity = 0);
    DataSet(DataSet& other);
    DataSet(DataSet* other);

    virtual ~DataSet() {}

    Attribute* attributeAt(int i)
    {
        return mAttributes.at(i);
    }
    void setAttribute(unsigned int i, Attribute* attr)
    {
        if (i >= mAttributes.size())
            throw runtime_error("input index is out the range of attribute's size");
        if(NULL != mAttributes[i] && mAttributes[i] != attr)
            delete mAttributes[i];
        mAttributes[i] = attr;
    }
    Attribute* targetAttribute()
    {
        if(mTagetIndex < 0)
            throw runtime_error("target index is not set");
        return attributeAt(mTagetIndex);
    }
    int targetIndex() const
    {
        return mTagetIndex;
    }
    int numTargets()
    {
        if(mTagetIndex < 0)
            throw new runtime_error("target index is not set");
        if(!targetAttribute()->isNominal())
            return 1;
        return targetAttribute()->numValues();
    }
    void setTarget(Attribute* attr)
    {
        mTagetIndex = attr->getIndex();
    }
    int numAttributes()
    {
        return mAttributes.size();
    }
    void setTargetIndex(int targetIndex)
    {
        if(targetIndex >= numAttributes())
            throw new runtime_error("invalid class index");
        mTagetIndex = targetIndex;
    }
#if 0
    inline vector<double> attributeToDoubleArray(Attribute& attr)
    {
        return attributeToDoubleArray(attr.index());
    }

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
    Instance* instance(int i)
    {
        return mInstances.at(i);
    }
    Instance* firstInstance()
    {
        vector<Instance *>::iterator i = mInstances.begin();
        if(i != mInstances.end())
            return *i;
    }
    Instance* lastInstance()
    {
        vector<Instance *>::reverse_iterator i = mInstances.rbegin();
        if(i != mInstances.rend())
            return *i;
    }
    double kthSmallestValue(Attribute* attr, int k)
    {
        return kthSmallestValue(attr->index(), k);
    }
    double kthSmallestValue(int attIndex, int k);

    double mean(Attribute& attr)
    {
        return mean(attr.index());
    }
    double mean(int attIndex);
    double variance(Attribute& attr)
    {
        return variance(attr.index());
    }
    double variance(int attIndex);

    int numInstances()
    {
        return mInstances.size();
    }
    void randomize()
    {
        for(int j = numInstances() - 1; j > 0; j--)
            swap(j, (int)(random() % (j + 1)));
    }


    void setRelationName(string& newName) 
    {
        mRelationName = newName;
    }
    const string& relationName() const
    {
        return mRelationName;
    }
    void sort(Attribute& attr)
    {
        sort(attr.index());
    }
    void sort(Attribute* attr)
    {
        sort(attr->index());
    }
    void sort(int attIndex);

    vector<double> attributeToDoubleArray(int attIndex);
    bool checkInstance(Instance& instance);

    void add(Instance* instance);
    void add(Instance& instance);

    void deleteAll();
    void deleteInstance(int index);
    void deleteAttributeAt(int position);
    void deleteWithMissing(int attIndex);

    DataSet* resample();
    DataSet* resampleWithWeights();
    DataSet* resampleWithWeights(vector<double>& weights);

    double sumOfWeights();
    void swap(int i, int j);

protected:
    /*
     * partition the instances into 2 sections, like qsort
     */
    int partition(int attIndex, int l, int r);
    void quickSort(int attIndex, int left, int right);
    int select(int attIndex, int left, int right, int k);
private:
    /*
     * move all instances with missing values to end
     * @return the position point to the last instance without missing value
     */
    int moveInstanceWithMissing();
#endif    
};

}

#endif /**/
