#include <special_functions.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"
using namespace std;
TEST(SpecailFunction, smoke){
    // Select a few input values
    double x[] = 
    {
        -3, 
        -1, 
        0.0, 
        0.5, 
        2.1 
    };
    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = 
    { 
        0.00134989803163, 
        0.158655253931, 
        0.5, 
        0.691462461274, 
        0.982135579437 
    };

    int numTests = sizeof(x)/sizeof(double);

    double maxError = 0.0;
    for (int i = 0; i < numTests; ++i)
    {
        double error = fabs(y[i] - mlplus::phi(x[i]));
        EXPECT_LT(error, 1e-10); 
        if (error > maxError)
            maxError = error;
    }
    EXPECT_LT(maxError, 1e-10); 
} 
