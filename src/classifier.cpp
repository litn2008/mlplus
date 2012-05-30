#include <algorithm>
#include "database.h"
#include "instance.h"
#include "attribute.h"
#include "classifier.h"

namespace mlplus
{
using namespace std;
Classifier::~Classifier()
{
}

double Classifier::classifyInstance(Instance* instance) const
{
    const vector<double> dist& = targetDistribution(instance);
    if(instance->targetAttribute()->isNominal())
    {
        return max_element(dist.begin(), dist.end()) - dist.begin();
    }
    else if(instance->targetAttribute()->isNumeric())
    {
        return dist[0];
    }
    return Instance::missingValue();
}

} // namespace mlplus

