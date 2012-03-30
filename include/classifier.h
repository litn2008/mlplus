#ifndef MLPLUS_CLASSIFIERS_CLASSIFIER_H
#ifndef MLPLUS_CLASSIFIERS_CLASSIFIER_H

#include <string>
#include <vector>

namespace mlplus
{
namespace classifiers
{
class Instance;
class DataSet;
class Classifier
{
protected:
    std::string mName;
    bool mDebug;

public:
    Classifier(const std::string& name) : mName(name)
    {
    }

    virtual ~Classifier();

    inline bool getDebug()
    {
        return mDebug;
    }

    inline void setDebug(bool value = true)
    {
        mDebug = value;
    }

    virtual void buildClassifier(Instances* data) = 0;
    virtual double classifyInstance(Instance* i) const;
    virtual void updateClassifier(Instance* instance) = 0;
    virtual std::vector<double> distributionForInstance(Instance * i) = 0;
};

} // namespace classifier
} // namespace mlplus

#endif
