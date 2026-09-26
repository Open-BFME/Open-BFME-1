// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x009C8130 is a two-argument leaf.  It samples four bytes at
// offsets 0, 2, 4, and 6 from four rows, where the row advance is twice the
// caller-supplied stride, and returns the resulting fixed-point dispersion.
// No named caller or class/vtable identity is present in the shipped xrefs;
// the RVA-derived spelling is therefore intentional.

int __cdecl rva009C8130(const unsigned char *src, int stride)
{
	unsigned int squareSum = 0;
	int y = 0;
	const unsigned char *p = src;
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
