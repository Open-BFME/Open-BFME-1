// Low-range filler of the codec spread tables (installed by
// bfmeInstallSpreadTable 0x009B3B40 as the MMX tier's slot 0..1 filler of
// both arrays and the SSE tier's array1 slot 0..1 filler). Scales the first
// coefficient by the first quantizer entry, rounds by (x + 15) >> 5 and
// splats the 16-bit result over all 64 output words; a zero first
// coefficient clears the 128-byte output instead.
#include <string.h>

void __cdecl Rva009C3CF0(const short *coeffs, const short *quant, short *out)
{
	short dc = coeffs[0];

	if (dc != 0)
	{
		unsigned int value = ((quant[0] * dc + 15) >> 5) & 0xffff;
		unsigned int *row = (unsigned int *)out;
		int i;

		value *= 0x10001;
		for (i = 8; i != 0; --i)
		{
			row[0] = value;
			row[1] = value;
			row[2] = value;
			row[3] = value;
			row += 4;
		}
	}
	else
	{
		memset(out, 0, 128);
	}
}
