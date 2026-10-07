// Byte-source sibling of bfmeGo7760: four-tap filter from an 8-bit source
// into an int table. Called by bfmeGo7820 (0x009A7820) and bfmeGo79D0.
void __cdecl bfmeGo76A0(
	int sourceAddress, int *table, void *sourcePitch, int sourceDelta,
	int rows, int columns, void *weights)
{
	const int *coefficient = (const int *)weights;
	for (unsigned int row = 0; row < (unsigned int)rows; ++row)
	{
		const unsigned char *&sourcePointer = *(const unsigned char **)&sourceAddress;
		unsigned int column = 0;
		if ((unsigned int)columns > 0)
		do
		{
			const unsigned char *previous = sourcePointer - sourceDelta;
			int value = sourcePointer[sourceDelta + sourceDelta] * coefficient[3];
			value += sourcePointer[0] * coefficient[1];
			value += sourcePointer[sourceDelta] * coefficient[2];
			value = (value + previous[0] * coefficient[0] + 0x40) >> 7;
			if (value < 0)
				value = 0;
			else if (value > 0xFF)
				value = 0xFF;
			++sourcePointer;
			table[column] = value;
			++column;
		}
		while (column < (unsigned int)columns);
		sourcePointer += (int)sourcePitch - columns;
		table += columns;
	}
}
