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
        cerr << args[0] << " <model_file> <input_data>\n";
        exit(0);
    }
    string str;
    ifstream ifs(args[2]);

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
        instances->add(instance);
    }
    dataset.setTargetIndex(0);

    ifstream model(args[1]);
    NaiveBayes bayes("sparse_classify", 6);
    bayes.setEventModel();
    bayes.load(model);
    //std::vector<double> vect = bayes.targetDistribution(instance);
    //copy(vect.begin(),vect.end(),ostream_iterator<double>( cout," " ));
    //cout << "\n";
    //pair<int, double> v = bayes.predict(instance);
    //cout << "predict:" << v.first << " with prob: " << v.second << endl;
    //

    AutoInstanceIteratorPtr instanceIt(dataset.newInstanceIterator());
    float all = 0;
    float right = 0;
    while(instanceIt->hasMore())
    {
        IInstance* ins = instanceIt->next();
        /*
        std::vector<double> vect = bayes.targetDistribution(ins);
        vector<double>::const_iterator it = max_element(vect.begin(), vect.end());
        int r = it - vect.begin();
        cout << ins->targetValue() << " v.s " << r << " with prob: ";
        */
        pair<int, double> v = bayes.predict(ins);
        if (v.first == ins->targetValue())
        {
            ++right;
        }
        ++all;
        //copy(vect.begin(),vect.end(),ostream_iterator<double>( cout," " ));
        cout << v.first << endl;
    }
    cerr << "Accurate:" << right/all << endl;
}
