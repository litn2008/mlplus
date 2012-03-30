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
    string mRelationName;
    vector<Attribute*> mAttributes;
    vector<Instance*> mInstances;
    int mTagetIndex;

protected:
    int partition(int attIndex, int l, int r);
    void quickSort(int attIndex, int left, int right);
    int select(int attIndex, int left, int right, int k);

public:
    DataSet(string& name, vector<Attribute*>& attrs, int capacity = 0);
    DataSet(DataSet& other);
    DataSet(DataSet* other);

    ~DataSet();

    Attribute* attribute(int i)
    {
        return mAttributes.at(i);
    }

    Attribute* attribute(string& name)
    {
        vector<Attribute *>::iterator i = mAttributes.begin();
        while(i != mAttributes.end())
            if((*i)->name() == name)
                return (*i);
        return NULL;
    }

    vector<double> attributeToDoubleArray(Attribute& attr)
    {
        return attributeToDoubleArray(attr.index());
    }

    bool checkForAttributeType(int attType)
    {
        vector<Attribute*>::iterator i = mAttributes.begin();
        while(i != mAttributes.end())
            if((*i)->type() == attType)
                return true;
        return false;
    }

    bool checkForStringAttributes()
    {
        return checkForAttributeType(Attribute::STRING);
    }

    Attribute* tagetAttribute()
    {
        if(mTagetIndex < 0)
            throw new runtime_error("class index is not set");
        return attribute(mTagetIndex);
    }

    int targetIndex()
    {
        return mTagetIndex;
    }

    void deleteWithMissing(Attribute * attr)
    {
        deleteWithMissing(attr->index());
    }

    void deleteWithMissingClass()
    {
        if(mTagetIndex < 0)
            throw new runtime_error("class index is not set");
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

    double kthSmallestValue(Attribute * attr, int k)
    {
        return kthSmallestValue(attr->index(), k);
    }

    double meanOrMode(Attribute& attr)
    {
        return meanOrMode(attr.index());
    }

    int numAttributes()
    {
        return mAttributes.size();
    }

    int numClasses()
    {
        if(mTagetIndex < 0)
            throw new runtime_error("class index is not set");
        if(!tagetAttribute()->isNominal())
            return 1;
        return tagetAttribute()->numValues();
    }

    int numDistinctValues(Attribute * attr)
    {
        return numDistinctValues(attr->index());
    }

    int numInstances()
    {
        return mInstances.size();
    }

    void randomize()
    {
        for(int j = numInstances() - 1; j > 0; j--)
            swap(j, (int)(random() % (j + 1)));
    }

    string relationName()
    {
        return mRelationName;
    }

    void setAttribute(int i, Attribute * attr)
    {
        if(mAttributes[i] != NULL)
            delete mAttributes[i];
        mAttributes[i] = attr;
    }

    void setTarget(Attribute * attr)
    {
        mTagetIndex = attr->index();
    }

    void setClassIndex(int targetIndex)
    {
        if(targetIndex >= numAttributes())
            throw new runtime_error("invalid class index");
        mTagetIndex = targetIndex;
    }

    void setRelationName(string& newName)
    {
        mRelationName = newName;
    }

    void sort(Attribute& attr)
    {
        sort(attr.index());
    }

    void sort(Attribute * attr)
    {
        sort(attr->index());
    }

    double variance(Attribute& attr)
    {
        return variance(attr.index());
    }

    void add(Instance* instance);
    void add(Instance& instance);
    vector<double> attributeToDoubleArray(int attIndex);
    bool checkInstance(Instance& instance);
    void deleteAll();
    void deleteInstance(int index);
    void deleteAttributeAt(int position);
    void deleteWithMissing(int attIndex);
    double kthSmallestValue(int attIndex, int k);
    double meanOrMode(int attIndex);
    int numDistinctValues(int attIndex);
    DataSet* resample();
    DataSet* resampleWithWeights();
    DataSet* resampleWithWeights(vector<double>& weights);
    void sort(int attIndex);
    double sumOfWeights();
    void swap(int i, int j);
    double variance(int attIndex);
};

}

#endif /**/
