#include <estimators/normal_estimator.h>
#include <estimators/discrete_estimator.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
using namespace std;
using namespace mlplus::estimators;
TEST(Estimator, smoke){
    NormalEstimator nes(1);
    nes.addValue(1, 1);
    nes.addValue(-1, 1);
    nes.addValue(2, 1);
    nes.addValue(-2, 1);
    nes.addValue(0, 2);
    EXPECT_EQ(nes.getMean(), 0);
    EXPECT_LT(fabs(nes.getStdDev() - 1.29099), 1e-5);
    EXPECT_LT(fabs(nes.getProbability(0) - 0.3), 1e-2);
} 
TEST(Estimator, DiscreteEstimator){
    DiscreteEstimator nes(3, true);
    nes.addValue(0, 19);
    nes.addValue(1, 9);
    nes.addValue(2, 9);
    EXPECT_EQ(nes.getNumOfClass(), 3);
    EXPECT_EQ(nes.getCount(0), 20);
    EXPECT_EQ(nes.getCount(1), 10);
    EXPECT_EQ(nes.getCount(2), 10);
    EXPECT_EQ(nes.getProbability(0), 0.5);
    EXPECT_EQ(nes.getProbability(1), 0.25);
    EXPECT_EQ(nes.getProbability(2), 0.25);
} 
