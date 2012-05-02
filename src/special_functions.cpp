#include "special_functions.h"
#include <cmath>
#define SQRTH	7.07106781186547524401E-1    
namespace mlplus
{
double phi(double a)
{
    double x, y, z;
    x = a * SQRTH;
    z = fabs(x);
    if(z < SQRTH)
    {
        y = 0.5 + 0.5 * erf(x);
    }
    else
    {
        y = 0.5 * erfc(z);
        if(x > 0)
            y = 1.0 - y;
    }
    return y;
}
}
