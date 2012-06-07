#ifndef MLPLU_ESTIMATORS_ESTIMATOR_INCLUDE_H
#define MLPLU_ESTIMATORS_ESTIMATOR_INCLUDE_H
#include "estimator.h"
#include "discrete_estimator.h"
#include "binary_estimator.h"
#include "normal_estimator.h"
namespace mlplus
{
namespace extractors
{
static unsigned nid = mlplus::estimators::NormalEstimator::getStaticID();
static unsigned bid = mlplus::estimators::BinaryEstimator::getStaticID();
static unsigned did = mlplus::estimators::DiscreteEstimator::getStaticID();
}
}
#endif
