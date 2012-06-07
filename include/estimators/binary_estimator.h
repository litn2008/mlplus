#ifndef MLPLUS_ESTIMATORS_BINARYESTIMATOR_H
#define MLPLUS_ESTIMATORS_BINARYESTIMATOR_H
#include "estimators/estimator.h"

namespace mlplus
{
namespace estimators
{
class BinaryEstimator: public IdentifiableEstimator<BinaryEstimator>
{
    double mPositiveCount;
    double mNegativeCount;
public:
    BinaryEstimator(bool laplace = 1);

    inline double getPostiveCount(void) const;
    inline double getNegativeCount(void) const;
    /*override*/ double getProbability(double postive);
    using Estimator::addValue;
    /*override*/ void addValue(double pos_or_nagtive, double weight);
    /*override*/std::string toString();
    /*override*/void fromString(const std::string&);

};
inline  double BinaryEstimator::getPostiveCount(void) const
{
    return mPositiveCount;
}
inline double BinaryEstimator::getNegativeCount() const
{
    return mNegativeCount;
}
} // namespace estimators
} // namespace mlplus

#endif 
