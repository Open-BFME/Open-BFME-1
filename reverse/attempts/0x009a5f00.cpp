// ?d_009a5f00@@YAXXZ
// partial score=0.7 date=2026-09-02
#include <math.h>

double bfmeGaussScale(double a, double b, double c)
{
    double x = c - b;
    double e = exp(-(a * a + a * a) / (x * x));
    return a * sqrt(6.2831853071795862) / e;
}
