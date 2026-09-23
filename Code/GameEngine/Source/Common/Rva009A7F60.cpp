// cl: /DNDEBUG /MD /O2
// Retail 0x009A7F60, 123 bytes. The matched Rva009A7FE0 caller passes a
// destination that this body advances one BYTE per column and writes with
// mov byte ptr. Its 0x009A7950 sibling instead writes 16-bit samples.
// Both compute (a*w0 + b*w1 + 0x40) >> 7 using the same seven-argument ABI.

void __cdecl Rva009A7F60(
	int *table,
	unsigned char *destination,
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
					destination[column] = (unsigned char)value;
					++source;
					++column;
				}
			while (column < (unsigned int)columns);
			}
			source = (int *)((char *)source + sourceStride);
			destination += columns;
		}
		while (--rowCount != 0);
	}
}
