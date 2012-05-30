#include "debug.h"
#include "instance.h"
#include "dataset.h"
#include "classifier.h"
#include "naive_bayes.h"
#include "iterator_interface.h"
#include "attribute_value.h"
#include "string_utility.h"
#include <estimators/discrete_estimator.h>
#include <estimators/normal_estimator.h>
#include <stdexcept>
#include <algorithm>
namespace mlplus
{
using namespace std;
NaiveBayes::NaiveBayes(const string& name, int nClasses):
    Classifier(name), mClassDistribution(NULL), mClassesCount(nClasses)
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

void NaiveBayes::train(DataSet* dataset)
{
    assert(dataset != NULL);
    //mClassesCount = dataset->numTargets();
    //int attributeCount  = dataset->numAttributes();
    setClassDistribution(new DiscreteEstimator(mClassesCount));
    int attIndex = 0;
    float numPrecision = DEFAULT_PRECISION;
    AutoAttributeIteratorPtr  attrIt(dataset->newAttributeIterator());
    while(attrIt->hasMore())
    {
        Attribute* attr = attrIt->next();
        attIndex = attr->getIndex();
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
            case Attribute::NOMINAL:
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

void NaiveBayes::update(IInstance* instance)
{
    if(instance->targetIsMissing())
        throw runtime_error("missing class in instance");
    const vector<ValueType>& valueArray = instance->getValueArray();
    int numAttri = valueArray.size();
    int targetValue = (int)instance->targetValue();
    for (int i = 0; i < numAttri; ++i)
    {
        if (!AttributeValue::isMissingValue(valueArray[i]))
        {
            int globalIndex = instance->getIndexAt(i);
            PosteriorProbability& pp = mDistributions[globalIndex];
            if (pp != NULL)
            {
                pp[targetValue]->addValue(valueArray[i],instance->getWeight());
            }
            else
            {
                //TODO log
            }
        }
    }
    mClassDistribution->addValue(targetValue, instance->getWeight());
}

vector<double> NaiveBayes::targetDistribution(IInstance* instance)
{
    //TODO: log-sum-exp trick
    //http://www.cs.ubc.ca/~murphyk/Teaching/CS340-Fall06/reading/NB.pdf
    // P(Y = c|x) = P(x|Y=c)P(Y=c)/C
    //          C = p(x|Y=c1)P(Y=c1) + p(x|Y=c2)P(Y=c2) + ........
    //
    // b_c = log(P(x|c)P(c))
    // log(P(Y=c|x) = b_c - log(exp(b_c1) + exp(b_c2) + ....)
    vector<double> v(mClassesCount);
    for(int i = 0; i < mClassesCount; i++)
        v[i] = mClassDistribution->getProbability(i);
    int attIndex = 0;
    const vector<ValueType>& valueArray = instance->getValueArray();
    for (unsigned i = 0; i < valueArray.size(); ++i)
    {
        if(!AttributeValue::isMissingValue(valueArray[i]))
        {
            double temp = 0, max = 0.0;
            attIndex = instance->getIndexAt(i);
            for(int j = 0; j < mClassesCount; j++)
            {
                temp = mDistributions[attIndex][j]->getProbability(valueArray[i]) *  
                    mClassDistribution->getProbability(j);
                //temp = mDistributions[attIndex][j]->getProbability(valueArray[i]);
                //temp = log(temp);
                if(temp < 1e-75) temp = 1e-75;
                v[j] *= temp;
                if(v[j] > max)
                {
                    max = v[j];
                }
            }
            if((max > 0.0) && (max < 1e-75))
                for(int j = 0; j < mClassesCount; j++)
                    v[j] *= 1e75;
        }
        attIndex++;
    }
    // normalize
    double sum = 0.0;
    for(int i = 0; i < mClassesCount; i++)
        sum += v[i];
    for(int i = 0; i < mClassesCount; i++)
        v[i] = v[i] / sum;
    return v;
}
void NaiveBayes::load(istream& input)
{
    string line;
    vector<string> result;
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
        mClassDistribution->fromString(line);
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
            if (typeid(NormalEstimator).name() == result[2])
            {
                if (NULL == pp[classid])
                {
                    pp[classid] = new NormalEstimator(0.1);
                }
                pp[classid]->fromString(result[3]);
            }
            else if (typeid(DiscreteEstimator).name() == result[2])
            {
                if (NULL == pp[classid])
                {
                    pp[classid] = new DiscreteEstimator(1);
                }
                pp[classid]->fromString(result[3]);
            }
        }
    }
}
void NaiveBayes::save(ostream& output)
{
    DistributionMapType::iterator it = mDistributions.begin();
    output << "class_count=" << mClassesCount << "\n";
    output << "class_dist=" <<  mClassDistribution->toString() << "\n";
    output << "#feature_count=" << mDistributions.size()<< "\n";
    output << "#featureid , classid, estimator_name, estimator_value\n";
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
                    output<<typeid(*pp[i]).name() << "," << pp[i]->toString() << "\n";
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

