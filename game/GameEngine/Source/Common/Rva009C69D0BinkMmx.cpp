// cl: /DNDEBUG /MD /O2
//
// Retail 0x009C69D0, 83 bytes.  Runs the two landed MMX Bink filters back to
// back over a 256-byte scratch strip: the horizontal pass at 0x009C6390 reads
// eleven rows starting one source stride above the requested row and writes
// them eight bytes wide into the scratch, then the four-tap vertical pass at
// 0x009C6470 reads the scratch from its second row and writes eight rows to
// the caller's destination.

// ?rva009C6390BinkMmx@@YAXPBXPAXHHHH0@Z
extern void __cdecl rva009C6390BinkMmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights);

// ?rva009C6470BinkMmx@@YAXPBXPAXHHHH0@Z
extern void __cdecl rva009C6470BinkMmx(const void *source, void *destination,
	int sourceStride, int unused, int count, int destinationStride,
	const void *weights);

// ?rva009C69D0BinkMmx@@YAXPBXPAXH00@Z
void __cdecl rva009C69D0BinkMmx(const void *source, void *destination,
	int sourceStride, const void *horizontalWeights,
	const void *verticalWeights)
{
	unsigned char scratch[256];

	rva009C6390BinkMmx(
		reinterpret_cast<const unsigned char *>(source) - sourceStride,
		scratch, sourceStride, 1, 11, 8, horizontalWeights);
	rva009C6470BinkMmx(scratch + 8, destination, 8, 8, 8, 8,
		verticalWeights);
}
