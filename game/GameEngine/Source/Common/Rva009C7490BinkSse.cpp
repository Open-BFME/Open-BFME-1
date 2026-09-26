// cl: /DNDEBUG /MD /O2
//
// Two-pass SSE2 Bink filter helper. The first pass filters eight horizontal
// rows into a 256-byte temporary buffer. The second pass filters eight rows
// from that buffer into the caller's destination.
// Retail 0x009C7490, 83 bytes.

extern void __cdecl rva009C6F20BinkSse(const void *, void *, int, int, int,
	int, const void *);
extern void __cdecl rva009C6FC0BinkSse(const void *, void *, int, int, int,
	int, const void *);

// ?rva009C7490BinkSse@@YAXPBEPAEHPBX2@Z
void __cdecl rva009C7490BinkSse(const unsigned char *source,
	unsigned char *destination, int stride, const void *horizontalWeights,
	const void *verticalWeights)
{
	unsigned char temporary[256];

	rva009C6F20BinkSse(source - stride, temporary, stride, 1, 0x0B, 8,
		horizontalWeights);
	rva009C6FC0BinkSse(temporary + 8, destination, 8, 8, 8, 8,
		verticalWeights);
}
