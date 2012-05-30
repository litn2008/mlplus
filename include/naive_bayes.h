#ifndef MLPLUS_CLASSIFIERS_BAYES_NAIVEBAYES
#define MLPLUS_CLASSIFIERS_BAYES_NAIVEBAYES

#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include "instance.h"
#include "dataset.h"
#include "classifier.h"
#include "estimators/estimator.h"
using namespace mlplus::estimators;
namespace mlplus
{
class NaiveBayes: public Classifier
{
public:
    typedef int AttributeIndex;
    typedef Estimator* EstimatorPtr;
    typedef EstimatorPtr* PosteriorProbability; 
    typedef std::map<AttributeIndex,  PosteriorProbability>  DistributionMapType;
private:
    std::map<AttributeIndex,  PosteriorProbability>  mDistributions;
    EstimatorPtr mClassDistribution;
    int mClassesCount;
    void release();
    NaiveBayes(const NaiveBayes& bas);
public:
    const static double  DEFAULT_PRECISION = 1;
    NaiveBayes(const string& name, int nClasses);
    virtual ~NaiveBayes();
    inline EstimatorPtr getDistribution(int attrIndex, int clsIndex);
    inline void setDistribution(int attrIndex, int clsIndex, EstimatorPtr est);
    inline EstimatorPtr getClassDistribution() const;
    inline void setClassDistribution(EstimatorPtr est);
    virtual void load(istream& input);
    virtual void save(ostream& output);
    virtual void train(DataSet* data);
    virtual std::pair<int, double> predict(IInstance* i);
    virtual void update(IInstance* instance);
    virtual std::vector<double> targetDistribution(IInstance* i);
};

inline  NaiveBayes::EstimatorPtr NaiveBayes::getDistribution(int attrIndex, int clsIndex) 
{
    if (clsIndex >= mClassesCount)
    {
        return NULL;
    }
    std::map<AttributeIndex,  PosteriorProbability>::const_iterator it = mDistributions.find(attrIndex);
    if (it != mDistributions.end())
    {
        return (it->second)[clsIndex];
    }
    return NULL;
}

inline void NaiveBayes::setDistribution(int attrIndex, int clsIndex, EstimatorPtr est)
{
    EstimatorPtr& p = mDistributions[attrIndex][clsIndex];
    if (NULL != p)
    {
        delete p;
    }
    p  = est;
}

inline  NaiveBayes::EstimatorPtr NaiveBayes::getClassDistribution(void) const
{
    return mClassDistribution;
}

inline void NaiveBayes::setClassDistribution(EstimatorPtr est)
{
    if (mClassDistribution)
    {
        delete mClassDistribution;
    }
    mClassDistribution = est;
}
} // namespace

#endif
