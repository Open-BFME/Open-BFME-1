// ?d_009c8130@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// VP6 4x4 sampled block variance at retail RVA 0x009C8130.

int Rva009C8130Vp6BlockVariance(unsigned char *src, int stride)
{
	int y = 0;
	unsigned char *p = src;
	unsigned int squareSum = 0;
	unsigned int sum = 0;

	while (y < 8) {
		sum += p[0] + p[2] + p[4] + p[6];
		squareSum += p[0] * p[0] + p[2] * p[2]
			+ p[4] * p[4] + p[6] * p[6];
		p += 2 * stride;
		y += 2;
	}

	return (16 * squareSum - sum * sum) >> 8;
}
