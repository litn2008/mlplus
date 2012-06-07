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
    DistributionMapType mDistributions;
    EstimatorPtr mClassDistribution;
    int mClassesCount;
    bool mEventModel;
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
    inline void setEventModel(bool v = true);
    inline bool getEventModel() const;
    virtual void load(istream& input);
    virtual void save(ostream& output);
    virtual void train(DataSet* data);
    virtual std::pair<int, double> predict(IInstance* i);
    virtual void update(IInstance* instance);
    virtual std::vector<double> targetDistribution(IInstance* i);
private:
    void trainBernoulli(DataSet* data);
    void trainMultinomial(DataSet* data);
    void updateBernoulli(IInstance* instance);
    void updateMultinomial(IInstance* instance);
    std::vector<double> predictBernoulli(IInstance* i);
    std::vector<double> predictMultinomial(IInstance* i);
    std::vector<double> scoreToProb(const std::vector<double>& score);
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

inline void NaiveBayes::setEventModel(bool v)
{
    mEventModel = v;
}

inline bool NaiveBayes::getEventModel() const
{
    return mEventModel;
}
} // namespace

#endif
