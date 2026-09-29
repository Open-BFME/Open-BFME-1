// cl: /DNDEBUG /MD /O2
//
// Dispatch the Bink two-tap SSE filter to the horizontal or vertical
// helper according to the distance between source rows. The packed
// coefficient pairs are 32-byte records at retail address 0x012D8C10.

extern const unsigned char g_012D8C10[];
extern void __cdecl rva009C7060BinkSse(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C70D0BinkSse(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C7140BinkSse(const void *, void *, int, const void *, const void *);

static const void *rva009C7380Weights(int index)
{
	return g_012D8C10 + index * 32;
}

void __cdecl rva009C7380BinkSse(const unsigned char *rowA, const unsigned char *rowB,
	void *destination, int stride, int horizontalIndex, int verticalIndex)
{
	int distance = rowB - rowA;
	if (distance < 0)
	{
		const unsigned char *oldRowA = rowA;
		rowA = rowB;
		distance = oldRowA - rowB;
	}
	if (distance == 1)
	{
		rva009C7060BinkSse(rowA, destination,
			stride, 1, 8, 8, rva009C7380Weights(horizontalIndex));
		return;
	}
	if (distance == stride)
	{
		rva009C70D0BinkSse(rowA, destination,
			stride, stride, 8, 8, rva009C7380Weights(verticalIndex));
		return;
	}
	if (distance == stride - 1)
	{
		rva009C7140BinkSse(rowA - 1, destination,
			stride, rva009C7380Weights(horizontalIndex),
			rva009C7380Weights(verticalIndex));
		return;
	}
	if (distance == stride + 1)
		rva009C7140BinkSse(rowA, destination,
			stride, rva009C7380Weights(horizontalIndex),
			rva009C7380Weights(verticalIndex));
}
