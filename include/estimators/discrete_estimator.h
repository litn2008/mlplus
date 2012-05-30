#ifndef MLPLUS_ESTIMATORS_DISCRETEESTIMATOR_H
#define MLPLUS_ESTIMATORS_DISCRETEESTIMATOR_H
#include "estimators/estimator.h"

namespace mlplus
{
namespace estimators
{
class DiscreteEstimator: public Estimator
{
    double* mCounts;
    double mSumOfCounts;
    int mNumOfClass;
public:
    DiscreteEstimator(const DiscreteEstimator&);
    DiscreteEstimator(int nSymbols, bool laplace = 1);
    DiscreteEstimator(int nSymbols, double fPrior);
    virtual ~DiscreteEstimator();
    inline int getNumOfClass(void) const;
    inline double getCount(int data) const;
    inline double getSumOfCounts(void) const;

    /*override*/ double getProbability(double data);
    using Estimator::addValue;
    /*override*/ void addValue(double data, double weight);
    /*override*/std::string toString();
    /*override*/void fromString(const std::string&);

};
inline int DiscreteEstimator::getNumOfClass(void) const
{
    return mNumOfClass;
}
inline double DiscreteEstimator::getCount(int data) const
{
    if(mSumOfCounts <= data)
        return 0;
    return mCounts[(int)data];
}
inline double DiscreteEstimator::getSumOfCounts(void) const
{
    return mSumOfCounts;
}

} // namespace estimators
} // namespace mlplus

#endif 
