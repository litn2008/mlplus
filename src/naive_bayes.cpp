#include <weka/core/Debug.h>
#include <weka/core/Instance.h>
#include <weka/core/Instances.h>
#include <weka/classifiers/Classifier.h>
#include <weka/estimators/DiscreteEstimator.h>
#include <weka/estimators/NormalEstimator.h>
#include <weka/classifiers/bayes/NaiveBayes.h>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <vector>

#ifdef HAVE_XERCESC
# include <xercesc/dom/DOM.hpp>
# include <xercesc/parsers/XercesDOMParser.hpp>
# include <xercesc/sax/InputSource.hpp>
# include <xercesc/util/BinInputStream.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/util/PlatformUtils.hpp>
#endif

namespace


namespace weka
{
namespace classifiers
{
namespace bayes
{

using namespace std;
using namespace weka::estimators;


NaiveBayes::NaiveBayes(string& name, int nClasses, int nAttributes) :
    Classifier(name),
    m_Distributions(NULL),
    m_ClassDistribution(NULL),
    m_nClasses(nClasses),
    m_nAttributes(nAttributes)
{
    // initialize distribution estimators if we've been dimensioned already
    if(nClasses != 0 && nAttributes != 0)
    {
        m_Distributions = new Estimator**[m_nAttributes - 1];
        if(m_Distributions == NULL)
            throw new runtime_error("out of memory");
        for(int i = 0; i < m_nAttributes - 1; i++)
        {
            m_Distributions[i] = new Estimator*[m_nClasses];
            if(m_Distributions[i] == NULL)
                throw new runtime_error("out of memory");
            for(int j = 0; j < m_nClasses; j++)
                m_Distributions[i][j] = NULL;
        }
    }
}

NaiveBayes::~NaiveBayes()
{
    if(m_Distributions != NULL)
    {
        for(int i = 0; i < m_nAttributes - 1; i++)
            if(m_Distributions[i] != NULL)
                delete [] m_Distributions[i];
        delete [] m_Distributions;
    }
}

void
NaiveBayes::buildClassifier(Instances * instances)
{
    // just assume classifiers built for training are not dimensioned at
    // instantiation time

    Debug.dprintf("%s: building classifier\n", __FUNCTION__);

    m_nClasses = instances->numClasses();
    m_nAttributes = instances->numAttributes();

    m_Distributions = new Estimator**[m_nAttributes - 1];
    if(m_Distributions == NULL)
        throw new runtime_error("out of memory");
    for(int i = 0; i < m_nAttributes - 1; i++)
    {
        m_Distributions[i] = new Estimator*[m_nClasses];
        if(m_Distributions[i] == NULL)
            throw new runtime_error("out of memory");
        for(int j = 0; j < m_nClasses; j++)
            m_Distributions[i][j] = NULL;
    }
    m_ClassDistribution = new DiscreteEstimator(m_nClasses, true);

    Instances trainInstances(instances);

    int attIndex = 0;
    for(int i = 0; i < m_nAttributes; i++)
    {
        Attribute * attr = trainInstances.attribute(i);
        double numPrecision = DEFAULT_PRECISION;
        if(attr->type() == Attribute::NUMERIC)
        {
            trainInstances.sort(attr);
            if((trainInstances.numInstances() > 0) &&
                    !trainInstances.instance(0)->isMissing(attr))
            {
                double lastVal = trainInstances.instance(0)->value(attr);
                double currentVal, deltaSum = 0;
                int distinct = 0;
                for(int j = 1; j < trainInstances.numInstances(); j++)
                {
                    Instance * currentInst = trainInstances.instance(j);
                    if(currentInst->isMissing(attr))
                        break;
                    currentVal = currentInst->value(attr);
                    if(currentVal != lastVal)
                    {
                        deltaSum += currentVal - lastVal;
                        lastVal = currentVal;
                        distinct++;
                    }
                }
                if(distinct > 0)
                    numPrecision = deltaSum / distinct;
            }
        }
        for(int j = 0; j < m_nClasses; j++)
        {
            switch(attr->type())
            {
            case Attribute::NUMERIC:
                m_Distributions[attIndex][j] =
                    new NormalEstimator(numPrecision);
                break;
            case Attribute::NOMINAL:
                m_Distributions[attIndex][j] =
                    new DiscreteEstimator(attr->numValues(), true);
                break;
            default:
                throw new runtime_error("unknown attribute type");
            }
        }
        attIndex++;
    }

    for(int i = 0; i < trainInstances.numInstances(); i++)
        updateClassifier(trainInstances.instance(i));
}

void NaiveBayes::updateClassifier(Instance * instance)
{
    if(instance->numAttributes() != m_nAttributes)
        throw new runtime_error("incorrect number of attributes in instance");
    if(instance->numClasses() != m_nClasses)
        throw new runtime_error("incorrect number of classes in instance");
    if(instance->classIsMissing())
        throw new runtime_error("missing class in instance");
    int attIndex = 0;
    for(int i = 0; i < m_nAttributes; i++)
    {
        Attribute * attr = instance->attribute(i);
        if(!instance->isMissing(attr))
        {
            m_Distributions[attIndex][(int)instance->classValue()]
            -> addValue(instance->value(attr), instance->weight());
        }
        attIndex++;
    }
    m_ClassDistribution->addValue(instance->classValue(), instance->weight());
}

vector<double> NaiveBayes::distributionForInstance(Instance * instance)
{
    if(instance->numAttributes() != m_nAttributes)
        throw new runtime_error("incorrect number of attributes in instance");
    vector<double> v(m_nClasses);
    for(int i = 0; i < m_nClasses; i++)
        v[i] = m_ClassDistribution->getProbability(i);
    int attIndex = 0;
    for(int i = 0; i < m_nAttributes; i++)
    {
        Attribute * attr = instance->attribute(i);
        if(!instance->isMissing(attr))
        {
            double temp, max = 0.0;
            for(int j = 0; j < m_nClasses; j++)
            {
                temp = m_Distributions[attIndex][j]
                       -> getProbability(instance->value(attr));
                if(temp < 1e-75)
                    temp = 1e-75;
                v[j] *= temp;
                if(v[j] > max)
                    max = v[j];
                if(isnan(v[j]))
                    throw new runtime_error("NaN returned from estimator for"
                                            " attribute");
            }
            if((max > 0.0) && (max < 1e-75))
                for(int j = 0; j < m_nClasses; j++)
                    v[j] *= 1e75;
        }
        attIndex++;
    }

    // normalize
    double sum = 0.0;
    for(int i = 0; i < m_nClasses; i++)
        sum += v[i];
    for(int i = 0; i < m_nClasses; i++)
        v[i] = v[i] / sum;

    return v;
}

} // namespace bayes
} // namespace classifiers
} // namespace mlplus

