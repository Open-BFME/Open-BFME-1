// cl: /DNDEBUG /MD

// Ported from Open BFME 2 Code/GameEngine/Source/Common/Rva009A75F0Vp6FourTapFilter.cpp.
// ?Rva009A75F0@@YAXPBEPAGIIIIPBH@Z
void __cdecl Rva009A75F0(
	const unsigned char *source,
	unsigned short *destination,
	unsigned int sourcePitch,
	unsigned int sourceDelta,
	unsigned int rows,
	unsigned int columns,
	const int *weights)
{
	unsigned int row;
	unsigned int column;
	int value;
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
			value = (source[2 * sourceDelta] * weights[3] + source[0] * weights[1] +
				source[sourceDelta] * weights[2] + source[-(int)sourceDelta] * weights[0] + 0x40) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			destination[column] = (unsigned short)value;
			source++;
		}
		source += sourcePitch - columns;
		destination += columns;
	}
}
