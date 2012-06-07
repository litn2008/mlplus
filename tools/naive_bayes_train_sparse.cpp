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
    if (argn < 2)
    {
        cerr << args[0] << " <input_data>\n";
        exit(0);
    }
    string str;
    ifstream ifs(args[1]);

    IAttributeContainer* attributes = new MapAttributeContainer();
    IInstanceContainer* instances = new SparseInstanceContainer();
    DataSet dataset("sparse_classify", attributes, instances);
    vector<string> attributeVector;
    IInstance* instance = NULL;
    while(getline(ifs, str))
    {
        split(attributeVector, str, is_any_of("\t "),token_compress_on);
        vector<ValueType> values;
        vector<int> indices;
        for(unsigned i = 0; i < attributeVector.size(); ++i)
        {
            if (attributeVector[i].empty()) continue;
            vector<string> kvs;
            split(kvs, attributeVector[i], is_any_of(":"));
            Attribute* target = new Attribute(kvs[0], Attribute::BINARY);//name of attribute
            int idcs = 0;
            ValueType value = 0;
            if (i != 0)
            {
                idcs = boost::lexical_cast<int, string>(kvs[0]);
                value = boost::lexical_cast<ValueType, string>(kvs.back());
            }
            else
            {
                value = boost::lexical_cast<ValueType, string>(kvs.back()) - 1;
            }
            target->setIndex(idcs);
            attributes->add(target);
            indices.push_back(idcs);
            values.push_back(value);
        }
        instance = new SparseInstance(values, indices, 1);
        instance->setDataset(&dataset);
        instance->setWeight(1);
        instances->add(instance);
    }
    dataset.setTargetIndex(0);
    NaiveBayes bayes("sparse_classify", 6);
    bayes.setEventModel();
    bayes.train(&dataset);
    //std::vector<double> vect = bayes.targetDistribution(instance);
    //copy(vect.begin(),vect.end(),ostream_iterator<double>( cout," " ));
    //cout << "\n";
    bayes.save(cout);
    //pair<int, double> v = bayes.predict(instance);
    //cout << "predict:" << v.first << " with prob: " << v.second << endl;
}
