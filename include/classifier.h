#ifndef MLPLUS_CLASSIFIERS_CLASSIFIER_H
#define MLPLUS_CLASSIFIERS_CLASSIFIER_H
#include <string>
#include <vector>
#include <utility>
namespace mlplus
{
class IInstance;
class DataSet;
class Classifier
{
private:
    std::string mName;
    bool mDebugMode;
public:
    Classifier(const std::string& name): mName(name), mDebugMode(false) {}
    virtual ~Classifier(){}
    inline bool getDebug();
    inline void setDebug(bool value = true);
    virtual void init(){};
    virtual void train(DataSet* data) = 0;
    virtual std::pair<int, double> predict(IInstance* i) = 0;
    virtual void update(IInstance* instance) = 0;
    virtual void load(istream& input) = 0;
    virtual void save(ostream& output) = 0;
    virtual std::vector<double> targetDistribution(IInstance* i) = 0;
};

inline bool Classifier::getDebug()
{
    return mDebugMode;
}
inline void Classifier::setDebug(bool value)
{
    mDebugMode = value;
}
} // namespace mlplus

#endif
