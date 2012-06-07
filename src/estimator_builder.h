#ifndef MLPLU_ESTIMATORS_ESTIMATOR_BUILDER_H
#define MLPLU_ESTIMATORS_ESTIMATOR_BUILDER_H
#include "estimator.h"
namespace mlplus
{
class EstimatorBuilder
{
public:
    static int class2Id(Estimator* p);
    static Estimator* id2Class(int id);
};
}
#endif
