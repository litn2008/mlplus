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
    /*
    string s = "This is,  a test";
    tokenizer<> tok(s);
    for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
        cout << *beg << "\n";
    */
    if (argn < 2)
    {
        cerr << args[0] << " <input_data>\n";
        exit(0);
    }
    string str;
    ifstream ifs(args[1]);
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
    dataset.setTarget(target);//last attribute is the target
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

    NaiveBayes bayes("wine_quality", 10);
    bayes.train(&dataset);
    std::vector<double> vect = bayes.targetDistribution(instance);
    //copy(vect.begin(),vect.end(),ostream_iterator<double>( cout," " ));
    //cout << "\n";
    bayes.save(cout);
    //pair<int, double> v = bayes.predict(instance);
    //cout << "predict:" << v.first << " with prob: " << v.second << endl;
}
