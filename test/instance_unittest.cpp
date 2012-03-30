#include <instance.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
using namespace mlplus;
using namespace std;
TEST(DataSetTest, smoke){
    Attribute name("name");
    EXPECT_TRUE(-INFINITY <= -INFINITY); 
    EXPECT_NE(name.getLowerBound(), NAN); 
    EXPECT_NE(name.getUpperBound(), NAN); 
    EXPECT_TRUE(name.upperBoundIsOpen()); 
    EXPECT_TRUE(name.lowerBoundIsOpen()); 
    EXPECT_FALSE(name.isInRange(-INFINITY)); 
    EXPECT_TRUE(name.isInRange(1)); 

    Attribute sex("sex");
    Attribute target("spam");

    vector<Attribute*> attrs;
    attrs.push_back(&name);
    name.setIndex(0);
    attrs.push_back(&sex);
    sex.setIndex(1);
    attrs.push_back(&target);
    target.setIndex(2); 

    DataSet* data = new DataSet("train_data", attrs);
    data->setTarget(&target);
    EXPECT_EQ(data->targetIndex(), 2); 
    EXPECT_EQ(data->targetAttribute(), &target); 
    EXPECT_EQ(data->attributeAt(0), &name); 
    EXPECT_EQ(data->numAttributes(), 3); 
    EXPECT_ANY_THROW(data->attributeAt(3)); 
    EXPECT_ANY_THROW(data->setAttribute(3, &name)); 
}

TEST(InstanceTest, smoke){
    Instance instance(10);
    EXPECT_NE(Instance::missingValue(), Instance::missingValue());
    EXPECT_TRUE(Instance::isMissingValue(Instance::missingValue()));
    EXPECT_TRUE(Instance::isMissingValue(0));
    EXPECT_TRUE(Instance::isMissingValue(-1));
    EXPECT_FALSE(instance.isSparse());
    EXPECT_EQ(instance.locate(0), 0);
    EXPECT_EQ(instance.getGroupId(), -1);
    instance.setGroupId(0);
    EXPECT_EQ(instance.getGroupId(), 0);
}
