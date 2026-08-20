// cl: /DNDEBUG /MD /EHsc

// Retail 0x00703B70. Sibling of 0x00703B60: fld arg; call __CIacos; ret.

#include <math.h>

// ?acos_00703b70@@YAMM@Z
float acos_00703b70(float v)
{
	return (float)acos(v);
}
