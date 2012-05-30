#include "estimators/normal_estimator.h"
#include "special_functions.h"
#include <cmath>
#include <stdexcept>
#include <sstream>
namespace mlplus
{
namespace estimators
{

using namespace std;

NormalEstimator::NormalEstimator(double precision) : 
    mPrecision(precision),mSumOfWeights(0), 
    mSumOfValues(0), mSumOfValuesSq(0),mMean(0), mStardardDev(precision / (2 * 3))
{
}
NormalEstimator::~NormalEstimator()
{
}

string  NormalEstimator::toString()
{
    ostringstream oss;
    oss << mPrecision << "\t" << mSumOfWeights <<"\t" << mSumOfValues <<"\t" <<
        mSumOfValuesSq << "\t" <<
        mMean <<"\t" << mStardardDev;
    return oss.str();
}
void  NormalEstimator::fromString(const string& str)
{
    istringstream iss(str,istringstream::in);
    iss >> mPrecision >> mSumOfWeights >> mSumOfValues >> mSumOfValuesSq >> mMean >> mStardardDev;
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

