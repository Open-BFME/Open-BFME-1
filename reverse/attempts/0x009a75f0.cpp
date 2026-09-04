// ?bfmeFilter75F0@@YAXPAEPAGHHHHPBH@Z
// partial score=0.78 date=2026-09-03
// Open-BFME5 conversion of the four-tap 16-bit filter helper.

void __cdecl bfmeFilter75F0(
	unsigned char *source,
	unsigned short *destination,
	int sourcePitch,
	int sourceDelta,
	int rows,
	int columns,
	const int *weights)
{
	if ((unsigned int)rows > 0)
	{
		int rowCount = rows;
		do
		{
			const int *coefficient = weights;
			int column = 0;
			unsigned char *previous = source - sourceDelta;
			unsigned char *next = source + sourceDelta;

			if ((unsigned int)columns > 0)
			{
				do
				{
					int value = next[sourceDelta] * coefficient[3];
					value += source[0] * coefficient[1];
					value += next[0] * coefficient[2];
					value += previous[0] * coefficient[0];
					value = (value + 0x40) >> 7;
					if (value < 0)
						value = 0;
					else if (value > 0xFF)
						value = 0xFF;
					destination[column] = (unsigned short)value;
					++source;
					++next;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columns);
			}

			source += sourcePitch - columns;
			destination += columns;
		}
		while (--rowCount != 0);
	}
}
