// ?bfmeGo7760@@YAXPAHPAXHHHH1@Z
// partial score=0.84 date=2026-09-03
// Clean C++ reconstruction of the retail four-tap VP6 word filter.

void __cdecl bfmeGo7760(
	int *table, void *destinationAddress, int sourcePitch, int sourceDelta,
	int rows, int columns, void *weights)
{
	if ((unsigned int)rows > 0)
	{
		int rowCount = rows;
		int *sourcePointer = table;
		do
		{
			int column = 0;
			if ((unsigned int)columns > 0)
			{
				int *previous = sourcePointer - sourceDelta;
				do
				{
					int value = sourcePointer[sourceDelta * 2] * ((int *)weights)[3];
					value += sourcePointer[sourceDelta] * ((int *)weights)[2];
					value += sourcePointer[0] * ((int *)weights)[1];
					value += previous[0] * ((int *)weights)[0];
					value = (value + 0x40) >> 7;
					if (value < 0)
						value = 0;
					else if (value > 0xFF)
						value = 0xFF;
					((unsigned short *)destinationAddress)[column] = (unsigned short)value;
					++sourcePointer;
					++previous;
					++column;
				}
				while ((unsigned int)column < (unsigned int)columns);
			}
			sourcePointer += sourcePitch - columns;
			destinationAddress = (unsigned char *)destinationAddress + columns * 2;
		}
		while (--rowCount != 0);
	}
}
