#include <attribute.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
using namespace mlplus;
using namespace std;
TEST(AttributeTest, create) {
    // Create numeric attributes "length" and "weight"
    Attribute* length = new Attribute("length");
    Attribute* weight = new Attribute("weight");
    // Create date attribute "date"
    //Attribute date = new Attribute("date", "yyyy-MM-dd HH:mm:ss");

    //Create vector to hold nominal values "first", "second", "third" 
    std::vector<string> nominal_values;
    nominal_values.push_back("first"); 
    nominal_values.push_back("second"); 
    nominal_values.push_back("third"); 

    // Create nominal attribute "position" 
    Attribute* position = new Attribute("position", nominal_values);
    EXPECT_EQ(position->getName(), "position");
    EXPECT_EQ(position->getWeight(), 0);
    EXPECT_TRUE(position->isNamedNominal());
    EXPECT_EQ(position->getIndex(), -1);
    EXPECT_EQ(position->getValue(0), "first"); 
    EXPECT_EQ(position->getValue(1), "second"); 
    EXPECT_EQ(position->getValue(2), "third"); 
    delete position;
    delete weight;
    delete length;
}
TEST(AttributeTest, smoke){
    std::vector<string> nominal_values;
    Attribute position("position", nominal_values);
    EXPECT_EQ(position.getName(), "position");
    EXPECT_EQ(position.getWeight(), 0);
    EXPECT_TRUE(position.isNamedNominal());
    EXPECT_EQ(position.getIndex(), -1);
    position.addValue("second");
    EXPECT_EQ(position.getValue(0), "second"); 
    EXPECT_TRUE(position.setValue(0, "first")); 
    EXPECT_EQ(position.getValue(0), "first"); 
    EXPECT_ANY_THROW(position.getValue(2)); 
    
    position.addValue("second");
    EXPECT_EQ(position.indexOfValue("first"), 0); 
    EXPECT_EQ(position.indexOfValue("second"), 1); 
    EXPECT_EQ(position.indexOfValue("1"), -1); 
    position.setIndex(1);
    EXPECT_EQ(position.getIndex(), 1); 

    EXPECT_TRUE(position.isInRange(1)); 
    EXPECT_EQ(position.numValues(), 2); 
    EXPECT_FALSE(position.isInRange(2)); 

}

TEST(AttributeTest, isInRange){
    Attribute attr("name");
    EXPECT_TRUE(-INFINITY <= -INFINITY); 
    EXPECT_NE(attr.getLowerBound(), NAN); 
    EXPECT_NE(attr.getUpperBound(), NAN); 
    EXPECT_TRUE(attr.upperBoundIsOpen()); 
    EXPECT_TRUE(attr.lowerBoundIsOpen()); 
    EXPECT_FALSE(attr.isInRange(-INFINITY)); 
    EXPECT_TRUE(attr.isInRange(1)); 
}
