// cl: /DNDEBUG /MD /EHsc

// Retail 0x00703C90. Sibling of 0x00703B60: fld arg; call __CIacos; ret.

#include <math.h>

// ?acos_00703c90@@YAMM@Z
float acos_00703c90(float v)
{
	return (float)acos(v);
}
