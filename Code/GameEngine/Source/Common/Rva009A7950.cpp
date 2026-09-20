// cl: /DNDEBUG /MD /O2

void __cdecl Rva009A7950(
	int *table,
	unsigned short *destination,
	int sourcePitch,
	int startIndex,
	int rows,
	int columns,
	const int *weights)
{
	if ((unsigned int)rows > 0)
	{
		int sourceStride = (sourcePitch - columns) * 4;
		unsigned int rowCount = (unsigned int)rows;
		int *source = table;
		do
		{
			unsigned int column = 0;
			if ((unsigned int)columns > 0)
			{
				do
				{
					int value = source[startIndex] * weights[1];
					value += source[0] * weights[0];
					value = (value + 0x40) >> 7;
					destination[column] = (unsigned short)value;
					++source;
					++column;
				}
			while (column < (unsigned int)columns);
			}
			source = (int *)((char *)source + sourceStride);
			destination = (unsigned short *)((char *)destination + columns * 2);
		}
		while (--rowCount != 0);
	}
}
