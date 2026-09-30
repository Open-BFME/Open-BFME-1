// cl: /DNDEBUG /MD /O2
// Scalar VP6 fractional-pixel block predictor at retail 0x009A7B00 (spread-table slot B54).
// Tables: four-tap weights at 0x012D7798 and two-tap weights at 0x012D7818, eight modes each.

extern const int g_012D7798[8][4];
extern const int g_012D7818[8][2];

extern void __cdecl d_009a75f0(void);
extern void __cdecl bfmeGo7820(void *, void *, void *, void *, void *);
extern void __cdecl Rva009A79D0Vp6Filter(
	const unsigned char *, unsigned short *, int, const int *, const int *);

typedef void (__cdecl *Rva009A7B00FourTapFilter)(
	const unsigned char *, unsigned short *, unsigned int, unsigned int,
	unsigned int, unsigned int, const int *);

// Two-tap 8-bit to 16-bit filter; retail inlines it (standalone copy at 0x009A7870).
static void Rva009A7B00TwoTapFilter(
	const unsigned char *source,
	unsigned short *destination,
	unsigned int sourcePitch,
	unsigned int pixelStep,
	unsigned int rows,
	unsigned int columns,
	const int *weights)
{
	unsigned int row;
	unsigned int column;
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
			destination[column] = (unsigned short)(
				(source[pixelStep] * weights[1] + source[0] * weights[0] + 0x40) >> 7);
			source++;
		}
		source += sourcePitch - columns;
		destination += columns;
	}
}

void __cdecl Rva009A7B00Vp6Filter(
	const unsigned char *source1,
	const unsigned char *source2,
	unsigned short *destination,
	unsigned int sourcePitch,
	int modeX,
	int modeY,
	int useBicubic)
{
	int diff = source2 - source1;
	if (diff < 0)
	{
		const unsigned char *temp = source1;
		source1 = source2;
		source2 = temp;
		diff = source2 - source1;
	}

	if (diff == 1)
	{
		if (useBicubic)
			((Rva009A7B00FourTapFilter)&d_009a75f0)(source1, destination, sourcePitch, 1, 8, 8, g_012D7798[modeX]);
		else
			Rva009A7B00TwoTapFilter(source1, destination, sourcePitch, 1, 8, 8, g_012D7818[modeX]);
	}
	else if (diff == (int)sourcePitch)
	{
		if (useBicubic)
			((Rva009A7B00FourTapFilter)&d_009a75f0)(source1, destination, sourcePitch, sourcePitch, 8, 8, g_012D7798[modeY]);
		else
			Rva009A7B00TwoTapFilter(source1, destination, sourcePitch, sourcePitch, 8, 8, g_012D7818[modeY]);
	}
	else if (diff == (int)(sourcePitch - 1))
	{
		if (useBicubic)
			bfmeGo7820((void *)(source1 - 1), destination, (void *)sourcePitch,
				(void *)g_012D7798[modeX], (void *)g_012D7798[modeY]);
		else
			Rva009A79D0Vp6Filter(source1 - 1, destination, sourcePitch, g_012D7818[modeX], g_012D7818[modeY]);
	}
	else if (diff == (int)(sourcePitch + 1))
	{
		if (useBicubic)
			bfmeGo7820((void *)source1, destination, (void *)sourcePitch,
				(void *)g_012D7798[modeX], (void *)g_012D7798[modeY]);
		else
			Rva009A79D0Vp6Filter(source1, destination, sourcePitch, g_012D7818[modeX], g_012D7818[modeY]);
	}
}
