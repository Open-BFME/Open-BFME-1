// Address-derived identity: no named owner is proven for retail 0x009A7EF0.
// The decoded seven-argument ABI and byte-interpolation formula match the
// neighboring Rva009A7F60 filter; this body writes one output byte per column.
void __cdecl Rva009A7EF0(
	const unsigned char *source,
	unsigned char *destination,
	int sourcePitch,
	int startIndex,
	int rows,
	int columns,
	const int *weights)
{
	if ((unsigned int)rows > 0)
	{
		unsigned int rowCount = (unsigned int)rows;
		const unsigned char *sourcePointer = source;
		do
		{
			unsigned int column = 0;
			if ((unsigned int)columns > 0)
			{
				do
				{
					int value = sourcePointer[startIndex] * weights[1];
					value += sourcePointer[0] * weights[0];
					value = (value + 0x40) >> 7;
					destination[column] = (unsigned char)value;
					++sourcePointer;
					++column;
				}
				while (column < (unsigned int)columns);
			}
			sourcePointer += sourcePitch - columns;
			destination += columns;
			--rowCount;
		}
		while (rowCount != 0);
	}
}
