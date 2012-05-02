#include "estimators/normal_estimator.h"
#include "special_functions.h"
#include <cmath>
#include <stdexcept>
namespace mlplus
{
namespace estimators
{

using namespace std;

NormalEstimator::~NormalEstimator()
{
}

void NormalEstimator::addValue(double data, double weight)
{
    if(weight == 0)
        return;
    data = round(data);
    mSumOfWeights += weight;
    mSumOfValues += data * weight;
    mSumOfValuesSq += data * data * weight;
    if(mSumOfWeights > 0)
    {
        mMean = mSumOfValues / mSumOfWeights;
        double stdDev = sqrt(fabs(mSumOfValuesSq/mSumOfWeights - mMean * mMean));
        if(stdDev > 1e-10)
        {
            if(mPrecision / (2.0 * 3.0) > stdDev)
            {
                mStardardDev = mPrecision / (2.0 * 3.0);
            }
            else
            {
                mStardardDev = stdDev;
            }
        }
    }
}

double NormalEstimator::getProbability(double data)
{
    data = round(data);
    double zLower = (data - mMean - (mPrecision / 2.0)) / mStardardDev;
    double zUpper = (data - mMean + (mPrecision / 2.0)) / mStardardDev;
    double pLower = phi(zLower);
    double pUpper = phi(zUpper);
    return pUpper - pLower;
}

} // namespace estimators
} // namespace mlplus

