#ifndef MLPLU_ESTIMATORS_ESTIMATOR_H
#define MLPLU_ESTIMATORS_ESTIMATOR_H
#include <string>
namespace mlplus
{
class Instance;
class DateSet;
namespace estimators
{
class Estimator
{
public:
    Estimator();
    Estimator(const Estimator&) {}
    virtual ~Estimator();
    //virtual void addValues(DataSet* data, int attrIndex);
    virtual void addValue(double data, double weight) = 0;
    virtual double getProbability(double data) = 0;
    virtual unsigned int getID() = 0;
    virtual std::string toString() = 0;
    virtual void fromString(const std::string&) = 0;
    virtual double logScore(int nType);
};
/**
 * thread unsafe
 * */
struct EstimatorID
{
    typedef unsigned int Type;
    static Type sNextID;
};

template <class Derived>
class IdentifiableEstimator: public Estimator
{
private:
    typedef EstimatorID::Type IDType;
    static IDType sID;
public:
    IdentifiableEstimator()
    {
        if(sID == 0)
        {
            sID = ++EstimatorID::sNextID;
        }
    }
    static IDType getStaticID()
    {
        if(sID == 0)
        {
            sID = ++EstimatorID::sNextID;
        }
        return sID;
    }
    unsigned int getID()
    {
        return sID;
    }
};

template <class Derived>
EstimatorID::Type IdentifiableEstimator<Derived>::sID = 0;// namespace estimators
} // namespace mlplus
}
#endif

