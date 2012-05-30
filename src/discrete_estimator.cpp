#include <cmath>
#include <sstream>
#include <stdexcept>
#include "estimators/estimator.h"
#include "estimators/discrete_estimator.h"
namespace mlplus
{
namespace estimators
{

using namespace std;

DiscreteEstimator::DiscreteEstimator(const DiscreteEstimator& other):
    Estimator(other), mCounts(NULL),
    mSumOfCounts(other.mSumOfCounts), mNumOfClass(other.mNumOfClass)
{
    mCounts = new double[other.mNumOfClass];
}
void DiscreteEstimator::addValue(double data, double weight)
{
    if(mSumOfCounts <= data)
    {
        return;
    }
    mCounts[(int)data] += weight;
    mSumOfCounts += weight;
}

DiscreteEstimator::DiscreteEstimator(int nSymbols, bool laplace)
{
    mNumOfClass = nSymbols;
    mCounts = new double[nSymbols];
    mSumOfCounts = 0;
    if(laplace)
    {
        for(int i = 0; i < nSymbols; i++)
            mCounts[i] = 1.0;
        mSumOfCounts = (double) nSymbols;
    }
}
double DiscreteEstimator::getProbability(double data)
{
    if(mSumOfCounts == 0)
        return 0;
    return (double)mCounts[(int)data] / mSumOfCounts;
}
DiscreteEstimator::DiscreteEstimator(int nSymbols, double fPrior)
{
    mNumOfClass = nSymbols;
    mCounts = new double[nSymbols];
    for(int i = 0; i < nSymbols; ++i)
        mCounts[i] = fPrior;
    mSumOfCounts = fPrior * (double) nSymbols;
}

DiscreteEstimator::~DiscreteEstimator()
{
    if(mCounts != NULL)
    {
        delete [] mCounts;
    }
    mCounts = NULL;
}

std::string DiscreteEstimator::toString()
{
    ostringstream oss;
    oss << mSumOfCounts << "\t" << mNumOfClass << "\t";
    for (int i = 0; i < mNumOfClass; ++i)
    {
        oss << mCounts[i] << "\t";
    }
    return oss.str();
}
void DiscreteEstimator::fromString(const std::string&)
{
    istringstream iss;
    iss >> mSumOfCounts >> mNumOfClass;
    if (NULL != mCounts)
    {
        delete mCounts;
    }
    mCounts = new double[mNumOfClass];
    for (int i = 0; i < mNumOfClass; ++i)
    {
        iss >> mCounts[i];
    }
}
} // namespace estimators
} // namespace mlplus

