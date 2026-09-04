// ?bfmeGo76A0@@YAXPAHPAXHHH1@Z
// partial score=0.78 date=2026-09-03
// Open-BFME5 conversion of the four-tap 32-bit filter helper.

void __cdecl bfmeGo76A0(
	int sourceAddress,
	int *destination,
	void *sourcePitch,
	int sourceDelta,
	int rows,
	int columns,
	void *weights)
{
	if ((unsigned int)rows > 0)
	{
		int columnCount = columns;
		const int *coefficient = (const int *)weights;
		int rowCount = rows;
		int delta = sourceDelta;
		unsigned char *sourcePointer = (unsigned char *)sourceAddress;

		do
		{
			int column = 0;
			unsigned char *previous = sourcePointer - delta;
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
					destination[column] = value;
					++sourcePointer;
					++next;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columnCount);
			}

			sourcePointer += (int)sourcePitch - columnCount;
			destination += columnCount;
		}
		while (--rowCount != 0);
	}
}
