#include <mlplus/core/Instances.h>
#include <mlplus/core/Instance.h>
#include <mlplus/core/Attribute.h>
#include <mlplus/classifiers/Classifier.h>

namespace mlplus
{
namespace classifiers
{

using namespace std;

Classifier::~Classifier()
{
}

double Classifier::classifyInstance(Instance * instance) const
{
    const vector<double> dist& = distributionForInstance(instance);
    switch(instance->classAttribute()->type())
    {
    case Attribute::NOMINAL:
    {
        double max = 0;
        int maxIndex = 0;
        for(int i = 0; i < (int)dist.size(); i++)
        {
            if(dist[i] > max)
            {
                maxIndex = i;
                max = dist[i];
            }
        }
        if(max > 0)
	{
	   return maxIndex;
	}
    }
    break;
    case Attribute::NUMERIC:
        return dist[0];
    default:
        break;
    }
    return Instance::missingValue();
}

} // namespace classifiers
} // namespace mlplus

