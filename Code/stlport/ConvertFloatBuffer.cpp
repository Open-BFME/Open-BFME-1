// cl: /O2 /EHsc /MD
// stlport
// STLport 4.5.3 __convert_float_buffer from src/num_put.cpp.

#include "stlport_prefix.h"
#include <stl/_ctype.h>

void __cdecl bfmeReplaceWords(unsigned short *, unsigned short *,
	const unsigned short *, const unsigned short *);

_STLP_BEGIN_NAMESPACE

wchar_t *_STLP_CALL
__convert_float_buffer(const char *first, const char *last,
	wchar_t *dest, const ctype<wchar_t> &ct, wchar_t decimal_point)
{
	ct.widen(first, last, dest);
	if (ct.widen('.') != decimal_point)
	{
		wchar_t dot = ct.widen('.');
		bfmeReplaceWords((unsigned short *)dest,
			(unsigned short *)(dest + (last - first)),
			(const unsigned short *)&dot,
			(const unsigned short *)&decimal_point);
	}
	return dest + (last - first);
}

_STLP_END_NAMESPACE
