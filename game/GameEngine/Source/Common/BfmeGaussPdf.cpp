// cl: /DNDEBUG /MD /O2

#include <math.h>

// ?bfmeGaussPdf@@YANNNN@Z
double __cdecl bfmeGaussPdf(double a, double b, double c)
{
	return exp(-((c - b) * (c - b)) / (a * a + a * a)) / (a * sqrt(6.2831853071795862));
}
