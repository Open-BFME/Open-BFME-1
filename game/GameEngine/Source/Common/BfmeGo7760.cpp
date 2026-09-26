void __cdecl bfmeGo7760(
	int *table, void *destinationAddress, int sourcePitch, int sourceDelta,
	int rows, int columns, void *weights)
{
	if ((unsigned int)rows > 0)
	{
		int columnCount = columns;
		const int *coefficient = (const int *)weights;
		int stride = (sourcePitch - columnCount) * 4;
		int rowCount = rows;
		int *sourcePointer = table;
		do
		{
			int column = 0;
			if ((unsigned int)columnCount > 0)
			{
				int *previous = sourcePointer - sourceDelta;
				do
				{
					int value = sourcePointer[sourceDelta * 2] * coefficient[3];
					value += sourcePointer[sourceDelta] * coefficient[2];
					value += sourcePointer[0] * coefficient[1];
					value += previous[0] * coefficient[0];
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
				while ((unsigned int)column < (unsigned int)columnCount);
			}
			sourcePointer = (int *)((unsigned char *)sourcePointer + stride);
			destinationAddress = (unsigned char *)destinationAddress + columnCount * 2;
		}
		while (--rowCount != 0);
	}
}
