// ?d_009a79d0@@YAXXZ
// partial score=0.9 date=2026-09-11
extern int g_bfmeTableC7E0;

extern void __cdecl Rva009A7950(
	int *, unsigned short *, int, int, int, int, const int *);

// Scalar VP6 8x8 interpolation helper at retail RVA 0x009A79D0.
void __cdecl Rva009A79D0Vp6Filter(
    const unsigned char *source,
	unsigned short *destination,
	int sourcePitch,
	const int *horizontalWeights,
	const int *verticalWeights)
{
    int sourceDelta = sourcePitch;
    sourceDelta -= 8;
    int *table = &g_bfmeTableC7E0;
    table += 2;
    int rows = 9;
    const unsigned char *sourcePointer = source;

    do
    {
        table[-2] = (sourcePointer[0] * horizontalWeights[0] +
                     sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[-1] = (sourcePointer[0] * horizontalWeights[0] +
                     sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[0] = (sourcePointer[0] * horizontalWeights[0] +
                    sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[1] = (sourcePointer[0] * horizontalWeights[0] +
                    sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[2] = (sourcePointer[0] * horizontalWeights[0] +
                    sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[3] = (sourcePointer[0] * horizontalWeights[0] +
                    sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[4] = (sourcePointer[0] * horizontalWeights[0] +
                    sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;
        table[5] = (sourcePointer[0] * horizontalWeights[0] +
                    sourcePointer[1] * horizontalWeights[1] + 0x40) >> 7;
        sourcePointer++;

        sourcePointer += sourceDelta;
		table += 8;
		--rows;
	}
	while (rows != 0);

	Rva009A7950(&g_bfmeTableC7E0, destination, 8, 8, 8, 8, verticalWeights);
}
