#include "naive_bayes.h"
#include "dataset.h"
#include "attribute_container.h"
#include "instance_container.h"
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;
using namespace boost;
using namespace mlplus;
using namespace mlplus::estimators;
int main(int argn, char** args)
{
    if (argn < 3)
    {
        cerr << args[0] << " <model_file> <test_data>\n";
        exit(0);
    }
    string str;
    ifstream ifs(args[2]);
    getline(ifs, str);
    vector<string> attributeVector;
    VectorAttributeContainer* attributes = new VectorAttributeContainer();
    DenseInstanceContainer* instances = new DenseInstanceContainer();
    DataSet dataset("wine_quality", attributes, instances);

    split(attributeVector, str, is_any_of(";"));
    vector<string>::iterator it = attributeVector.begin();
    Attribute* target = NULL;
    for (unsigned int i = 0; i < attributeVector.size(); ++i)
    {
        target = new Attribute(attributeVector[i]);
        target->setIndex(i);
        attributes->add(target);
    }
    DenseInstance* instance = NULL;
    while(getline(ifs, str))
    {
        split(attributeVector, str, is_any_of(";"));
        vector<ValueType> values;
        std::transform(attributeVector.begin(), attributeVector.end(),
            std::back_inserter(values),boost::lexical_cast<ValueType, string>);
        instance = new DenseInstance(values);
        instance->setDataset(&dataset);
        instances->add(instance);
    }
    dataset.setTarget(target);
    NaiveBayes bayes("wine_quality", 10);
    ifstream model(args[1]);
    bayes.load(model);
    //std::vector<double> vect = bayes.targetDistribution(instance);
    //copy(vect.begin(),vect.end(),ostream_iterator<double>( cout," " ));
    //cout << "\n";
    AutoInstanceIteratorPtr instanceIt(dataset.newInstanceIterator());
    while(instanceIt->hasMore())
    {
        IInstance* ins = instanceIt->next();
        pair<int, double> v = bayes.predict(ins);
        cout << ins->targetValue() << " v.s " << v.first << " with prob: " << v.second << endl;
    }
}
