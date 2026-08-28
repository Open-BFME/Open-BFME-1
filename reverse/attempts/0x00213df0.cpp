// ?d_00213df0@@YAXXZ
// partial score=0.55 date=2026-08-27
// cl: /DNDEBUG /MD /EHsc /O1 /Ob1 /D_STLP_USE_STATIC_LIB
// Open-BFME5: retail 0x00213DF0 (19 bytes), two-word clear helper.

#include <string.h>

class Rva00213DF0
{
public:
	void clear(int *values);
};

void Rva00213DF0::clear(int *values)
{
	int zero;
	memset(&zero, 0, sizeof(zero));
	values[0] = zero;
	values[1] = zero;
}
