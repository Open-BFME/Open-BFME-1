// cl: /DNDEBUG /MD /EHsc

// Retail 0x00716550. Sibling of 0x00716520: inline x87 exp(float).

#include <math.h>

// ?exp_00716550@@YAMM@Z
float exp_00716550(float v)
{
	return (float)exp(v);
}
