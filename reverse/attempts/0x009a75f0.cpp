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
	int rowCount = rows;
	int columnCount = columns;
	const int *coefficient = weights;
	if ((unsigned int)rowCount > 0)
	{
		int delta = sourceDelta;
		unsigned char *sourcePointer = source;
		do
		{
			int column = 0;
			register unsigned char *previous = sourcePointer - delta;
			unsigned char *next = sourcePointer + delta;

			if ((unsigned int)columnCount > 0)
			{
				do
				{
					int value = next[delta] * coefficient[3];
					value += sourcePointer[0] * coefficient[1];
					value += next[0] * coefficient[2];
					value += previous[0] * coefficient[0];
					value = (value + 0x40) >> 7;
					if (value < 0)
						value = 0;
					else if (value > 0xFF)
						value = 0xFF;
					destination[column] = (unsigned short)value;
					++sourcePointer;
					++next;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columnCount);
			}

			sourcePointer += sourcePitch - columnCount;
			destination += columnCount;
		}
		while (--rowCount != 0);
	}
}
