#ifndef __WEKACPP_CLASSIFIERS_BAYES_NAIVEBAYES__
#define __WEKACPP_CLASSIFIERS_BAYES_NAIVEBAYES__

#include <weka/core/Instance.h>
#include <weka/core/Instances.h>
#include <weka/estimators/Estimator.h>
#include <weka/classifiers/Classifier.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace mlplus
{

class NaiveBayes : public Classifier
{
    Estimator *** m_Distributions;
    Estimator * m_ClassDistribution;

public:
    static const double DEFAULT_PRECISION = 0.01;

    static NaiveBayes* fromXML(streambuf * s);
    static NaiveBayes* fromXML(streambuf& s);
    static NaiveBayes* fromXML(string& xml);

    int m_nClasses;
    int m_nAttributes;

    NaiveBayes(string& name, int nClasses = 0, int nAttributes = 0);

    virtual ~NaiveBayes();

    Estimator* getDistribution(int attrIndex, int clsIndex)
    {
        if(attrIndex < 0 || attrIndex >= m_nAttributes)
            throw new runtime_error("attribute index out of range");
        if(clsIndex < 0 || clsIndex >= m_nClasses)
            throw new runtime_error("class index out of range");
        return m_Distributions[attrIndex][clsIndex];
    }

    void setDistribution(int attrIndex, int clsIndex, Estimator * est)
    {
        if(attrIndex < 0 || attrIndex >= m_nAttributes)
            throw new runtime_error("attribute index out of range");
        if(clsIndex < 0 || clsIndex >= m_nClasses)
            throw new runtime_error("class index out of range");
        if(m_Distributions[attrIndex][clsIndex] != NULL)
            delete m_Distributions[attrIndex][clsIndex];
        m_Distributions[attrIndex][clsIndex] = est;
    }

    Estimator* getClassDistribution(void)
    {
        return m_ClassDistribution;
    }

    void setClassDistribution(Estimator * est)
    {
        if(m_ClassDistribution != NULL)
            delete m_ClassDistribution;
        m_ClassDistribution = est;
    }

    void buildClassifier(Instances * instances);
    void updateClassifier(Instance * instance);
    vector<double> distributionForInstance(Instance * instance);

    void XMLDTD(streambuf * s);
    void toXML(streambuf * s);
    void XMLDTD(streambuf& s);
    void toXML(streambuf& s);
    void XMLDTD(string& xml);
    void toXML(string& xml);
};

} // namespace 

#endif 
