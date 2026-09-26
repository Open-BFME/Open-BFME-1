// cl: /DNDEBUG /MD /EHsc

// Retail 0x00716520. Inline x87 exp(float).

#include <math.h>

// ?exp_00716520@@YAMM@Z
float exp_00716520(float v)
{
	return (float)exp(v);
}
