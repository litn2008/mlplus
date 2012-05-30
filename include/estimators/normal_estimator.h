#ifndef MLPLUS_ESTIMATORS_NORMALESTIMATOR_H
#define MLPLUS_ESTIMATORS_NORMALESTIMATOR_H
#include "estimators/estimator.h"
#include <cmath>
#include <stdexcept>

namespace mlplus
{
namespace estimators
{
using namespace std;

class NormalEstimator: public Estimator
{
public:
    double mPrecision;
    double mSumOfWeights;
    double mSumOfValues;
    double mSumOfValuesSq; //+= data * data * weight
    double mMean;
    double mStardardDev;
public:
    NormalEstimator(double precision);
    virtual ~NormalEstimator();
    /*override*/string toString();
    /*override*/void fromString(const std::string&);
    double round(double data)
    {
        return rint(data / mPrecision) * mPrecision;
    }
    using Estimator::addValue;
    /*override*/void addValue(double data, double weight);
    /*override*/double getProbability(double data);
    double getMean() const { return mMean;}
    double getStdDev() const  { return mStardardDev;}
    double getPrecision() const { return mPrecision;}
    void setPrecision(double pre) {mPrecision = pre;}
};

} // namespace estimators
} // namespace mlplus

#endif 
