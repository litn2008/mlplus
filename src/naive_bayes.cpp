#include "debug.h"
#include "instance.h"
#include "dataset.h"
#include "classifier.h"
#include "naive_bayes.h"
#include "iterator_interface.h"
#include "attribute_value.h"
#include "string_utility.h"
#include <estimators/estimator_include.h>
#include <stdexcept>
#include <algorithm>
namespace mlplus
{
using namespace std;
NaiveBayes::NaiveBayes(const string& name, int nClasses):
    Classifier(name), mClassDistribution(NULL), mClassesCount(nClasses),mEventModel(false)
{
}

void NaiveBayes::release()
{
    std::map<AttributeIndex,  PosteriorProbability>::iterator it = mDistributions.begin();
    for(; it != mDistributions.end(); ++it)
    {
        PosteriorProbability& pp = it->second;
        if (pp != NULL)
        {
            for (int i = 0; i < mClassesCount; ++i)
            {
                if(pp[i] != NULL)
                {
                    delete pp[i];
                    pp[i] = NULL;
                }
            }
            delete[] pp;
            pp = NULL;
        }
    }
    if (mClassDistribution != NULL)
    {
        delete mClassDistribution;
        mClassDistribution = NULL;
    }
}
NaiveBayes::~NaiveBayes()
{
    release();
}

void NaiveBayes::trainBernoulli(DataSet* dataset)
{
    assert(dataset != NULL);
    //mClassesCount = dataset->numTargets();
    //int attributeCount  = dataset->numAttributes();
    setClassDistribution(new DiscreteEstimator(mClassesCount));
    int attIndex = 0;
    float numPrecision = DEFAULT_PRECISION;
    AutoAttributeIteratorPtr  attrIt(dataset->newAttributeIterator());
    int targetIndex = dataset->targetIndex();
    while(attrIt->hasMore())
    {
        Attribute* attr = attrIt->next();
        attIndex = attr->getIndex();
        if (attIndex == targetIndex)
        {
            continue;
        }
        if(attr->isNumeric())
        {
            vector<ValueType> attributeCol = dataset->attributeArray(*attr);
            std::sort(attributeCol.begin(), attributeCol.end());
            if (!attributeCol.empty())
            {
                vector<ValueType>::iterator it = attributeCol.begin();
                float lastVal = *it;
                float deltaSum = 0;
                int distinct = 0;
                for(;it != attributeCol.end(); ++it)
                {
                    if(*it != lastVal)
                    {
                        deltaSum += *it - lastVal;
                        lastVal = *it;
                        distinct++;
                    }
                }
                if(distinct > 0)
                {
                    numPrecision = deltaSum / distinct;
                }
            }
        }
        for(int j = 0; j < mClassesCount; j++)
        {
            PosteriorProbability& pp =  mDistributions[attIndex];
            if (pp == NULL)
            {
                pp = new EstimatorPtr[mClassesCount];
                memset(pp, 0, sizeof(EstimatorPtr)*mClassesCount);
            }
            switch(attr->getType())
            {
            case Attribute::NUMERIC:
                pp[j] = new NormalEstimator(numPrecision);
                break;
            case Attribute::BINARY:
                pp[j] = new  BinaryEstimator();
                break;
            case Attribute::COMPACTNOMINAL:
            case Attribute::NAMEDNOMINAL:
            case Attribute::STRING:
                pp[j] = new DiscreteEstimator(attr->numValues());
                break;
            default:
                throw runtime_error("unknown attribute type:" + attr->toString());
            }
        }
    }
    AutoInstanceIteratorPtr instanceIt(dataset->newInstanceIterator());
    while(instanceIt->hasMore())
    {
        update(instanceIt->next());
    }
}
void NaiveBayes::trainMultinomial(DataSet* dataset)
{
    assert(dataset != NULL);
    //mClassesCount = dataset->numTargets();
    //int attributeCount  = dataset->numAttributes();
    setClassDistribution(new DiscreteEstimator(mClassesCount));
    AutoAttributeIteratorPtr  attrIt(dataset->newAttributeIterator());
    PosteriorProbability& pp =  mDistributions[0];//only one "training attribute" with
    if (pp == NULL)
    {
        pp = new EstimatorPtr[mClassesCount];
        memset(pp, 0, sizeof(EstimatorPtr)*mClassesCount);
    }
    for(int j = 0; j < mClassesCount; j++)
    {
        pp[j] = new DiscreteEstimator(dataset->numAttributes());
    }
    AutoInstanceIteratorPtr instanceIt(dataset->newInstanceIterator());
    while(instanceIt->hasMore())
    {
        update(instanceIt->next());
    }
}

void NaiveBayes::train(DataSet* dataset)
{
    if (mEventModel)
    {
        trainMultinomial(dataset);
    }
    else
    {
        trainBernoulli(dataset);
    }
}

void  NaiveBayes::updateBernoulli(IInstance* instance)
{
    if(instance->targetIsMissing())
        throw runtime_error("missing class in instance");
    int targetValue = (int)instance->targetValue();
    int targetIndex = instance->targetIndex();
    DistributionMapType::iterator it = mDistributions.begin();
    for (; it != mDistributions.end(); ++it)
    {
        if (it->first == targetIndex)
        {
            continue;
        }
        PosteriorProbability& pp = it->second;
        if (NULL != pp)
        {
            ValueType value = instance->getValue(it->first);
            if (!AttributeValue::isMissingValue(value))
            {
                pp[targetValue]->addValue(value,value*instance->getWeight());
            }
            else
            {
                pp[targetValue]->addValue(0,instance->getWeight());
            }
        }
    }
    mClassDistribution->addValue(targetValue, instance->getWeight());
}
void  NaiveBayes::updateMultinomial(IInstance* instance)
{
    if(instance->targetIsMissing())
        throw runtime_error("missing class in instance");
    int targetValue = (int)instance->targetValue();
    int targetIndex = instance->targetIndex();
    PosteriorProbability& pp =  mDistributions[0];
    float tfAll = 0;
    if (NULL != pp)
    {
        int numAttr = instance->numAttributes();
        for (int i = 0; i < numAttr; ++i)
        {
            int aIndex = instance->attributeIndex(i);
            if (aIndex == targetIndex)
            {
                continue;
            }
            ValueType value = instance->getValue(aIndex);
            if (!AttributeValue::isMissingValue(value))
            {
                pp[targetValue]->addValue(aIndex, value*instance->getWeight());
                tfAll += value * instance->getWeight();
            }
        }
    }
    mClassDistribution->addValue(targetValue, tfAll);
}
void  NaiveBayes::update(IInstance* instance)
{
    if (mEventModel)
    {
        updateMultinomial(instance);
    }
    else
    {
        updateBernoulli(instance);
    }
}

std::vector<double> NaiveBayes::predictBernoulli(IInstance* instance)
{
    vector<double> v(mClassesCount,0);
    for(int i = 0; i < mClassesCount; i++)
    {
        v[i] = log(mClassDistribution->getProbability(i));
    }
    int attIndex = 0;
    const vector<ValueType>& valueArray = instance->getValueArray();
    for (unsigned i = 0; i < valueArray.size(); ++i)
    {
        if(!AttributeValue::isMissingValue(valueArray[i]))
        {
            double temp = 0;
            attIndex = instance->attributeIndex(i);
            if (mDistributions.find(attIndex) == mDistributions.end())
            {
                continue;
            }
            for(int j = 0; j < mClassesCount; j++)
            {
                temp = mDistributions[attIndex][j]->getProbability(valueArray[i]);
                v[j] += log(temp);
            }
        }
        attIndex++;
    }
    return scoreToProb(v);
}
std::vector<double> NaiveBayes::predictMultinomial(IInstance* instance)
{
    vector<double> v(mClassesCount,0);
    for(int i = 0; i < mClassesCount; i++)
    {
        v[i] = log(mClassDistribution->getProbability(i));
    }
    int numAttr = instance->numAttributes();
    int targetIndex = instance->targetIndex();
    PosteriorProbability& pp = mDistributions[0];
    for (int i = 0; i < numAttr; ++i)
    {
        int aIndex = instance->attributeIndex(i);
        if (aIndex == targetIndex)
        {
            continue;
        }
        ValueType aValue = instance->getValue(aIndex);
        if(!AttributeValue::isMissingValue(aValue))
        {
            double temp = 0;
            for(int j = 0; j < mClassesCount; j++)
            {
                temp = pp[j]->getProbability(aIndex);
                v[j] += log(temp) * aValue;
            }
        }
    }
    return scoreToProb(v);
}

vector<double> NaiveBayes::scoreToProb(const vector<double>& score)
{
    int class_set_size = score.size();
    vector<double> prb(class_set_size, 0);
    for (int i = 0; i < class_set_size; i++) 
    {
        double delta_prb_sum = 0.0;
        for (int j = 0; j < class_set_size; j++) 
        {
            delta_prb_sum += exp(score[j] - score[i]);
        }
        prb[i] = 1/delta_prb_sum;
    }
    //normalize
    double sum;
    for (int i = 0; i < class_set_size; ++i)
    {
        sum += prb[i];
    }
    for (int i = 0; i < class_set_size; ++i)
    {
        prb[i] /= sum;
    }
    return prb;
}

vector<double> NaiveBayes::targetDistribution(IInstance* instance)
{
    if (mEventModel)
    {
        return predictMultinomial(instance);
    }
    return predictBernoulli(instance);
}
void NaiveBayes::load(istream& input)
{
    string line;
    vector<string> result;
    //event model
    if (getline(input,line))
    {
        split(line,result,"=");
        mEventModel = atoi(result[1].c_str());
    }
    //class count
    if (getline(input,line))
    {
        split(line,result,"=");
        mClassesCount = atoi(result[1].c_str());
        setClassDistribution(new DiscreteEstimator(mClassesCount));
    }
    //class distribution
    if (getline(input,line))
    {
        split(line,result,"=");
        mClassDistribution->fromString(result.back());
    }
    //attribues
    while(getline(input, line))
    {
        if ('#' == line[0])
        {
            continue;
        }
        vector<string> result;
        split(line, result, ",");
        if (4 == result.size())
        {
            int attIndex = atoi(result[0].c_str());
            PosteriorProbability& pp =  mDistributions[attIndex];
            if (pp == NULL)
            {
                pp = new EstimatorPtr[mClassesCount];
                memset(pp, 0, sizeof(EstimatorPtr)*mClassesCount);
            }
            int classid = atoi(result[1].c_str());
            unsigned int estimatorId = atoi(result[2].c_str()); 
            if (estimatorId == NormalEstimator::getStaticID())
            {
                if (NULL == pp[classid])
                {
                    pp[classid] = new NormalEstimator(0.1);
                }
                pp[classid]->fromString(result[3]);
            }
            else if (estimatorId == DiscreteEstimator::getStaticID())
            {
                if (NULL == pp[classid])
                {
                    pp[classid] = new DiscreteEstimator(1);
                }
                pp[classid]->fromString(result[3]);
            }
            else if (estimatorId == BinaryEstimator::getStaticID())
            {
                if (NULL == pp[classid])
                {
                    pp[classid] = new BinaryEstimator();
                }
                pp[classid]->fromString(result[3]);
            }
        }
    }
}
void NaiveBayes::save(ostream& output)
{
    DistributionMapType::iterator it = mDistributions.begin();
    output << "model=" << mEventModel << "\n";
    output << "class_count=" << mClassesCount << "\n";
    output << "class_dist=" <<  mClassDistribution->toString() << "\n";
    output << "#feature_count=" << mDistributions.size()<< "\n";
    output << "#featureid , targetid, estimator_id, estimator_string\n";
    for(; it != mDistributions.end(); ++it)
    {
        PosteriorProbability& pp = it->second;
        if (pp != NULL)
        {
            //feature id
            for (int i = 0; i < mClassesCount; ++i)
            {
                if(NULL != pp[i])
                {
                    output << it->first << "," << i << "," ;
                    output<<pp[i]->getID() << "," << pp[i]->toString() << "\n";
                }
            }
        }
    }
}
pair<int, double> NaiveBayes::predict(IInstance* i) 
{
    vector<double> array = targetDistribution(i);
    vector<double>::const_iterator it = max_element(array.begin(), array.end());
    return make_pair(it - array.begin(), *it);
}
} // namespace mlplus

