#include <instance.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "attribute_container.h"
#include "attribute_value.h"
#include "dataset.h"
using namespace mlplus;
using namespace std;

TEST(DataSetTest, smoke){
    SharedAttributePtr name(new Attribute("name"));
    EXPECT_TRUE(-INFINITY <= -INFINITY); 
    EXPECT_NE(name->getLowerBound(), NAN); 
    EXPECT_NE(name->getUpperBound(), NAN); 
    EXPECT_TRUE(name->upperBoundIsOpen()); 
    EXPECT_TRUE(name->lowerBoundIsOpen()); 
    EXPECT_FALSE(name->isInRange(-INFINITY)); 
    EXPECT_TRUE(name->isInRange(1)); 

    SharedAttributePtr sex(new Attribute("sex"));
    SharedAttributePtr target(new Attribute("spam"));

    vector<SharedAttributePtr> attrs;
    attrs.push_back(name);
    name->setIndex(0);
    attrs.push_back(sex);
    sex->setIndex(1);
    attrs.push_back(target);
    target->setIndex(2); 

    DataSet* data = new DataSet("train_data", new VectorAttributeContainer(attrs));
    data->setTargetIndex(target->getIndex());
    EXPECT_EQ(data->targetIndex(), 2); 
    EXPECT_EQ(data->targetAttribute(), target.get()); 
    EXPECT_EQ(data->attributeAt(0), name.get()); 
    EXPECT_EQ(data->numAttributes(), 3); 
    EXPECT_FALSE(data->attributeAt(3)); 
    EXPECT_FALSE(data->setAttribute(3, name.get())); 

    DenseInstance instance(10);
    instance.setDataset(data);
    EXPECT_FALSE(instance.isSparse());
    EXPECT_EQ(instance.getGroupId(), -1);
    instance.setGroupId(0);
    EXPECT_EQ(instance.getGroupId(), 0);
    EXPECT_EQ(instance.numAttributes(), 10);
    EXPECT_EQ(instance.numTargets(), 1);
    EXPECT_EQ(instance.numValues(), 10);
    EXPECT_TRUE(instance.hasMissingValue());
    instance.setValue(0, 1);
    instance.setValue(1, 2);
    instance.setValue(2, 3);
    instance.setValue(3, 4);
    instance.setValue(11, 4);

    EXPECT_EQ(instance.getValue(0), 1);
    EXPECT_EQ(instance.getValue(1), 2);
    EXPECT_EQ(instance.numAttributes(), 12);
    instance.setMissing(1);
    EXPECT_NE(instance.getValue(1), 2);

    Attribute* a = instance.attributeAt(0);
    instance.setValue(*a, 10.0f);
    EXPECT_EQ(instance.getValue(a), 10);
    EXPECT_EQ(instance.getValue(0), 10);
    EXPECT_FALSE(instance.isMissing(*a));
    EXPECT_TRUE(instance.isMissing(*instance.attributeAt(1)));

    EXPECT_EQ(instance.getWeight(), 1);
    instance.setWeight(0);
    EXPECT_EQ(instance.getWeight(), 0);

    instance.setTargetValue(10);
    EXPECT_EQ(instance.targetValue(), 10);
};

