#include "dataset.h"
#include "estimators/estimator.h"
#include <stdexcept>
namespace mlplus
{
namespace estimators
{
using namespace std;

Estimator::Estimator()
{
}
Estimator::~Estimator()
{
}
/*
void Estimator::addValues(DataSet* data, int attrIndex)
{
    AutoInstanceIteratorPtr it = data->newInstanceIterator();
    while(it->hasMore())
    {
        IInstance* p = it->next();
        addValue(p->getValue(attrIndex), 1.0);
    }
}
*/
double Estimator::logScore(int)
{
    throw runtime_error("not implemented");
    return NAN;
}

} // namespace estimators
} // namespace mlplus
