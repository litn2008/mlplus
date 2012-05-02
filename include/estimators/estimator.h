#ifndef MLPLU_ESTIMATORS_ESTIMATOR_H
#define MLPLU_ESTIMATORS_ESTIMATOR_H
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
    Estimator(const Estimator&){}
    virtual ~Estimator();
    //virtual void addValues(DataSet* data, int attrIndex);
    virtual void addValue(double data, double weight) = 0;
    virtual double getProbability(double data) = 0;
    virtual double logScore(int nType);
};

} // namespace estimators
} // namespace mlplus

#endif

