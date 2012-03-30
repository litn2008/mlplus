#include <stdexcept>
#include <vector>
#include "dataset.h"
namespace mlplus
{

using namespace std;

DataSet::DataSet(const string& name, vector<Attribute*>& attrs, int capacity):
    mName(name), mAttributes(attrs), mTagetIndex(-1)
{
    mInstances.reserve(capacity);
}
#if 0
int DataSet::partition(int attIndex, int l, int r)
{
    double pivot = instance((l + r) / 2)->value(attIndex);
    while(l < r)
    {
        while((instance(l)->value(attIndex) < pivot) && (l < r))
            l++;
        while((instance(r)->value(attIndex) > pivot) && (l < r))
            r--;
        if(l < r)
        {
            swap(l, r);
            l++;
            r--;
        }
    }
    if((l == r) && (instance(r)->value(attIndex) > pivot))
        r--;
    return r;
}

void DataSet::quickSort(int attIndex, int left, int right)
{
    if(left < right)
    {
        int middle = partition(attIndex, left, right);
        quickSort(attIndex, left, middle);
        quickSort(attIndex, middle + 1, right);
    }
}

int DataSet::select(int attIndex, int left, int right, int k)
{
    if(left == right)
    {
        return left;
    }
    else
    {
        int middle = partition(attIndex, left, right);
        if((middle - left + 1) >= k)
        {
            return select(attIndex, left, middle, k);
        }
        else
        {
            return select(attIndex, middle + 1, right,
                          k - (middle - left + 1));
        }
    }
}

DataSet::DataSet(string& name, vector<Attribute *>& attrs,
                     int capacity) :
    mRelationName(name)
{
    mAttributes.resize(attrs.size());
    for(int i = 0; i < (int)attrs.size(); i++)
        mAttributes[i] = attrs[i]->clone();
}

DataSet::DataSet(DataSet& other) :
    mRelationName(other.relationName())
{
    m_ClassIndex = other.m_ClassIndex;
    mAttributes.resize(other.mAttributes.size());
    for(int i = 0; i < (int)other.mAttributes.size(); i++)
        mAttributes[i] = other.mAttributes[i]->clone();
    mInstances.resize(other.mInstances.size());
    for(int i = 0; i < (int)other.mInstances.size(); i++)
        mInstances[i] = new Instance(other.mInstances[i]);
}

DataSet::DataSet(DataSet * other) :
    mRelationName(other->relationName())
{
    m_ClassIndex = other->m_ClassIndex;
    mAttributes.resize(other->mAttributes.size());
    for(int i = 0; i < (int)other->mAttributes.size(); i++)
        mAttributes[i] = other->mAttributes[i]->clone();
    mInstances.resize(other->mInstances.size());
    for(int i = 0; i < (int)other->mInstances.size(); i++)
        mInstances[i] = new Instance(other->mInstances[i]);
}

DataSet::~DataSet()
{
    for(int i = 0; i < (int)mInstances.size(); i++)
        if(mInstances[i] != NULL)
            delete mInstances[i];
    for(int i = 0; i < (int)mAttributes.size(); i++)
        if(mAttributes[i] != NULL)
            delete mAttributes[i];
}

void DataSet::add(Instance * instance)
{
    instance->setDataset(this);
    mInstances.push_back(instance);
}

void DataSet::add(Instance& instance)
{
    add(new Instance(instance));
}

vector<double> DataSet::attributeToDoubleArray(int index)
{
    vector <double> v;
    for(int i = 0; i < instance(i)->numValues(); i++)
        v[i] = instance(i)->value(index);
    return v;
}

bool DataSet::checkInstance(Instance& instance)
{
    if(instance.numAttributes() != numAttributes())
        return false;
    for(int i = 0; i < numAttributes(); i++)
    {
        if(instance.isMissing(i))
        {
            continue;
        }
        else if(attribute(i)->isNominal() || attribute(i)->isString())
        {
            if(instance.value(i) != (double)(int)instance.value(i))
            {
                return false;
            }
            else if((instance.value(i) < 0) ||
                    (instance.value(i) > attribute(i)->numValues()))
            {
                return false;
            }
        }
    }
    return true;
}

void DataSet::deleteAll()
{
    vector<Instance *>::iterator i = mInstances.begin();
    while(i != mInstances.end())
    {
        delete *i;
        i++;
    }
    mInstances.clear();
}

void DataSet::deleteInstance(int index)
{
    vector<Instance *>::iterator i = mInstances.begin();
    if(index == 0)
    {
        delete *i;
        mInstances.erase(i);
        return;
    }
    else
    {
        while(index && (i != mInstances.end()))
        {
            i++;
            if(--index == 0)
            {
                delete *i;
                mInstances.erase(i);
                return;
            }
        }
    }
    throw new runtime_error("index not found");
}

void DataSet::deleteWithMissing(int attIndex)
{
    vector<Instance *>::iterator i = mInstances.begin();
    while(i != mInstances.end())
    {
        if((*i)->isMissing(attIndex))
        {
            delete *i;
            i = mInstances.erase(i);
        }
        else
        {
            i++;
        }
    }
}

double DataSet::kthSmallestValue(int attIndex, int k)
{
    if(!attribute(attIndex)->isNumeric())
        throw new runtime_error("attribute must be numeric to compute "
                                "kth-smallest value");
    int j = moveInstanceWithMissing();
    // select instance
    if((k < 0) || (k > j))
        throw new runtime_error("value for k for computing kth-smallest "
                                "value too large");
    return instance(select(attIndex, 0, j, k))->value(attIndex);
}

double DataSet::mean(int attIndex)
{
    if(attribute(attIndex)->isNumeric())
    {
        double result = 0, found = 0;
        for(int j = 0; j < numInstances(); j++)
        {
            if(!instance(j)->isMissing(attIndex))
            {
                found += instance(j)->weight();
                result += instance(j)->weight() * instance(j)->value(attIndex);
            }
        }
        if(found <= 0)
        {
            return 0;
        }
        else
        {
            return result / found;
        }
    }
    return 0;
}

DataSet* DataSet::resample()
{
    DataSet * newData = new DataSet(mRelationName, mAttributes, 0);
    while(newData->numInstances() < numInstances())
        newData->add(new Instance(instance(random() % numInstances())));
    return newData;
}

DataSet* DataSet::resampleWithWeights()
{
    vector<double> weights;
    for(int i = 0; i < numInstances(); i++)
        weights[i] = instance(i)->weight();
    return resampleWithWeights(weights);
}

DataSet* DataSet::resampleWithWeights(vector<double>& weights)
{
    if((int)weights.size() != numInstances())
        throw new runtime_error("weights.length != numInstances");
    DataSet * newData = new DataSet(mRelationName, mAttributes, 0);
    if(numInstances() == 0)
        return newData;
    vector<double> probabilities;
    double sumProbs = 0;
    for(int i = 0; i < numInstances(); i++)
    {
        sumProbs += (double) random();
        probabilities[i] = sumProbs;
    }
    // normalize
    double sumWeights = sumOfWeights();
    for(int i = 0; i < (int)probabilities.size(); i++)
        probabilities[i] /= sumProbs / sumWeights;
    // make sure that rounding errors don't mess things up
    probabilities[numInstances() - 1] = sumWeights;
    int k = 0;
    int l = 0;
    sumProbs = 0;
    while((k < numInstances() && (l < numInstances())))
    {
        if(weights[l] < 0)
            throw new runtime_error("weights must be positive");
        sumProbs += weights[l];
        while((k < numInstances()) && (probabilities[k] <= sumProbs))
        {
            newData->add(new Instance(instance(l)));
            newData->instance(k)->setWeight(1);
            k++;
        }
        l++;
    }
    return newData;
}

int  DataSet::moveInstanceWithMissing()
{
    int i, j;
    j = numInstances() - 1;
    i = 0;
    while(i <= j)
    {
        if(instance(j)->isMissing(attIndex))
        {
            j--;
        }
        else
        {
            if(instance(i)->isMissing(attIndex))
            {
                swap(i, j);
                j--;
            }
            i++;
        }
    }
    return j;
}

void DataSet::sort(int attIndex)
{
    int j = moveInstanceWithMissing();
    quickSort(attIndex, 0, j);
}

double DataSet::sumOfWeights()
{
    double sum = 0;
    for(int i = 0; i < numInstances(); i++)
        sum += instance(i)->weight();
    return sum;
}

void DataSet::swap(int i, int j)
{
    Instance * temp = mInstances[i];
    mInstances[i] = mInstances[j];
    mInstances[j] = temp;
}

double DataSet::variance(int attIndex)
{
    if(!attribute(attIndex)->isNumeric())
        throw new runtime_error("attribute is not numeric at" + __FILE__);
    double sum = 0, sumSquared = 0, sumOfWeights = 0;
    for(int i = 0; i < numInstances(); i++)
    {
        if(!instance(i)->isMissing(attIndex))
        {
            sum += instance(i)->weight() * instance(i)->value(attIndex);
            sumSquared += instance(i)->weight() *
                          instance(i)->value(attIndex) *
                          instance(i)->value(attIndex);
            sumOfWeights += instance(i)->weight();
        }
    }
    if(sumOfWeights <= 1)
        return 0;
    double result = (sumSquared - (sum * sum / sumOfWeights)) /
                    (sumOfWeights - 1);
    if(result < 0)
    {
        return 0;
    }
    return result;
}

Attribute* DataSet::attribute(const string& name) 
{
    vector<Attribute*>::const_iterator i = mAttributes.begin();
    while(i != mAttributes.end())
    {
        if((*i)->name() == name)
            return (*i);
    }
    return NULL;
}

bool DataSet::checkForAttributeType(int attType) const
{
    vector<Attribute*>::iterator i = mAttributes.begin();
    while(i != mAttributes.end())
    {
        if((*i)->type() == attType)
            return true;
    }
    return false;
}
#endif
}

