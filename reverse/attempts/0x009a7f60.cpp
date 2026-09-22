// ?Rva009A7F60@@YAXPAHPAGHHHHPBH@Z
// partial score=0.87 date=2026-09-22
// cl: /DNDEBUG /MD /O2
//
// Retail 0x009A7F60, 123 bytes, a carved extent.  The VP6 two-tap row filter
// that is the BYTE-OUTPUT sibling of the matched Rva009A7950 at 0x009A7950
// (127 bytes): same seven arguments, same spilled row counter, same
// `(a*w0 + b*w1 + 0x40) >> 7`, same source stride of (pitch - columns) * 4.
// The two differences are visible in the bytes: this one stores through
// `mov byte ptr [ecx+ebp], dl` with no index scale, so the destination is a
// byte pointer, and it advances the destination by `columns` rather than by
// `columns * 2`.  reverse/symbols.csv pins the unsigned-short signature here
// from the sibling, which is why the body casts rather than re-typing the
// parameter -- the pin is a candidate name, and changing the parameter would
// change the mangled name it pins.
//
// Size is exact and every instruction in both loops, the spill slots and the
// epilogue are exact.  Sixteen bytes differ and all of them are one esi/edi
// exchange: retail puts the weights pointer in esi and the column count in
// edi, and VC7.1 reverses the pair because it schedules the stride subtraction
// (which uses the column count) before the weights pointer is ever read.
//
// Exhausted: a weights alias declared before the stride, the same alias hoisted
// above the row guard, a separate unsigned width local for the loop bound and
// the advance, the stride recomputed inside the outer loop, and the
// sib/register/loop/copy/store/frame sweep from tools/shape_family_levers.py,
// which offers one alternative for this shape.

void __cdecl Rva009A7F60(
	int *table,
	unsigned short *destination,
	int sourcePitch,
	int startIndex,
	int rows,
	int columns,
	const int *weights)
{
	if ((unsigned int)rows > 0)
	{
		int sourceStride = (sourcePitch - columns) * 4;
		unsigned int rowCount = (unsigned int)rows;
		int *source = table;
		unsigned char *output = (unsigned char *)destination;
		do
		{
			unsigned int column = 0;
			if ((unsigned int)columns > 0)
			{
				do
				{
					int value = source[startIndex] * weights[1];
					value += source[0] * weights[0];
					value = (value + 0x40) >> 7;
					output[column] = (unsigned char)value;
					++source;
					++column;
				}
			while (column < (unsigned int)columns);
			}
			source = (int *)((char *)source + sourceStride);
			output += columns;
		}
		while (--rowCount != 0);
	}
}
