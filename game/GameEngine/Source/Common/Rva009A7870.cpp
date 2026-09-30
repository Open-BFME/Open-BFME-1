// cl: /DNDEBUG /MD /O2
// Address-derived identity: retail 0x009A7870, 107 bytes, seven-argument cdecl.
// Two-tap unsigned-byte to unsigned-short filter. The same source pattern is
// inlined in the matched Rva009A7B00Vp6Filter at 0x009A7B00.
// Retail boundary: preceding int3 padding, ret at +0x6A, then int3 padding.
// No direct calls, global addresses, or relocation operands.
void __cdecl Rva009A7870(
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

