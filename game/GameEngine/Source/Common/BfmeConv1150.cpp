// cl: /Od
// Open-BFME5 conversions.

extern "C" void *__cdecl bfmeMalloc1150(unsigned int n);

extern "C" unsigned int g_bfmeHeapSize1150;
extern "C" char *g_bfmeHeapEnd1150;
extern "C" char *g_bfmeHeapCur1150;
extern "C" char *g_bfmeFreeList1150[];

char *bfmeChunk1150(unsigned int size, int *nobjs)
{
	char *n8;
	unsigned int n7;
	unsigned int n6;

	n6 = size * *nobjs;
	n7 = g_bfmeHeapEnd1150 - g_bfmeHeapCur1150;

	if (n7 >= n6) {
		n8 = g_bfmeHeapCur1150;
		g_bfmeHeapCur1150 += n6;
		return n8;
	} else if (n7 >= size) {
		*nobjs = (int)(n7 / size);
		n6 = size * *nobjs;
		n8 = g_bfmeHeapCur1150;
		g_bfmeHeapCur1150 += n6;
		return n8;
	} else {
		unsigned int n5 = 2 * n6 + (((g_bfmeHeapSize1150 >> 4) + 7) & ~7);

		if (n7 > 0) {
			char **n4 = g_bfmeFreeList1150 + ((n7 - 1) >> 3);

			*(char **)g_bfmeHeapCur1150 = *n4;
			*n4 = g_bfmeHeapCur1150;
		}

		g_bfmeHeapCur1150 = (char *)bfmeMalloc1150(n5);

		if (g_bfmeHeapCur1150 == 0) {
			unsigned int n2;
			char **n1;
			char *n3;

			for (n2 = size; n2 <= 0x80; n2 += 8) {
				n1 = g_bfmeFreeList1150 + ((n2 - 1) >> 3);
				n3 = *n1;
				if (n3 != 0) {
					*n1 = *(char **)n3;
					g_bfmeHeapCur1150 = n3;
					g_bfmeHeapEnd1150 = g_bfmeHeapCur1150 + n2;
					return bfmeChunk1150(size, nobjs);
				}
			}

			g_bfmeHeapEnd1150 = 0;
			g_bfmeHeapCur1150 = (char *)bfmeMalloc1150(n5);
		}

		g_bfmeHeapSize1150 += n5;
		g_bfmeHeapEnd1150 = g_bfmeHeapCur1150 + n5;
		return bfmeChunk1150(size, nobjs);
	}
}
