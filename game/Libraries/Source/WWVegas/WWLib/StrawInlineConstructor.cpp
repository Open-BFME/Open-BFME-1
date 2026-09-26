// cl: /O2 /Ob0
#include "straw.h"
#include <new>

Straw * __cdecl bfmeConstructStraw009216F0(void *where)
{
	return new (where) Straw;
}
