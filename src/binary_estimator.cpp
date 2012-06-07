#include <cmath>
#include <sstream>
#include <stdexcept>
#include "estimators/estimator.h"
#include "estimators/binary_estimator.h"
namespace mlplus
{
namespace estimators
{

using namespace std;


void BinaryEstimator::addValue(double val, double weight)
{
    if (val > 0.99) 
    {
        mPositiveCount += weight;
    }
    else
    {
        mNegativeCount += weight;
    }
}

BinaryEstimator::BinaryEstimator(bool laplace)
{
    mPositiveCount = laplace;
    mNegativeCount = laplace;
}
double BinaryEstimator::getProbability(double data)
{
    if(data > 0.9)
    {
        return mPositiveCount/(mPositiveCount + mNegativeCount);
    }
    return mNegativeCount/(mPositiveCount + mNegativeCount);
}

std::string BinaryEstimator::toString()
{
    ostringstream oss;
    oss << mPositiveCount << "\t" << mNegativeCount << "\t";
    return oss.str();
}
void BinaryEstimator::fromString(const std::string& str)
{
    istringstream iss(str);
    iss >> mPositiveCount >> mNegativeCount;
}
} // namespace estimators
} // namespace mlplus

