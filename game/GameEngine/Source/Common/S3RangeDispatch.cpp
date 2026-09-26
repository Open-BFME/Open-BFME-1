// Three six-argument dispatchers, 0x002610F0, 0x00437D30 and 0x00575A50.
//
// The range is a pointer pair over eight-byte elements: the count is
// sub then sar 3, signed, so the elements are eight bytes wide and the
// subtraction is ordinary pointer arithmetic. The first element is copied to
// the third argument as a whole struct -- two dwords through one register --
// before the call, and the call carries a literal zero in second place.

#include <stdarg.h>

struct BfmeRangeValue
{
	int m_bfmeFirst;
	int m_bfmeSecond;
};


void bfmeDispatchA(BfmeRangeValue *first, int zero, int count,
	void *third, void *fourth, void *fifth);		// ILT 0x000075D6

void bfmeDispatchB(BfmeRangeValue *first, int zero, int count,
	void *third, void *fourth, void *fifth);		// ILT 0x00028501

void bfmeDispatchC(BfmeRangeValue *first, int zero, int count,
	void *third, void *fourth, void *fifth);		// ILT 0x00027138

// ?bfmeRunRange_002610F0@@YAXPAUBfmeRangeValue@@00ZZ
void bfmeRunRange_002610F0(BfmeRangeValue *first, BfmeRangeValue *last, BfmeRangeValue *out, ...)
{
	va_list extra;

	va_start(extra, out);

	void *third = va_arg(extra, void *);
	void *fourth = va_arg(extra, void *);
	void *fifth = va_arg(extra, void *);

	va_end(extra);

	*out = *first;

	bfmeDispatchA(first, 0, last - first, third, fourth, fifth);
}

// ?bfmeRunRange_00437D30@@YAXPAUBfmeRangeValue@@00ZZ
void bfmeRunRange_00437D30(BfmeRangeValue *first, BfmeRangeValue *last, BfmeRangeValue *out, ...)
{
	va_list extra;

	va_start(extra, out);

	void *third = va_arg(extra, void *);
	void *fourth = va_arg(extra, void *);
	void *fifth = va_arg(extra, void *);

	va_end(extra);

	*out = *first;

	bfmeDispatchB(first, 0, last - first, third, fourth, fifth);
}

// ?bfmeRunRange_00575A50@@YAXPAUBfmeRangeValue@@00ZZ
void bfmeRunRange_00575A50(BfmeRangeValue *first, BfmeRangeValue *last, BfmeRangeValue *out, ...)
{
	va_list extra;

	va_start(extra, out);

	void *third = va_arg(extra, void *);
	void *fourth = va_arg(extra, void *);
	void *fifth = va_arg(extra, void *);

	va_end(extra);

	*out = *first;

	bfmeDispatchC(first, 0, last - first, third, fourth, fifth);
}
