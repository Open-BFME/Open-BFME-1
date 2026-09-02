// cl: /O2 /Ob0

// ?bfmeClampBlock@@YAXPAEPAFHH@Z
// Eight rows of eight signed 16-bit samples, each clamped to 0..255 and
// stored as a byte. Inner eight are written out so MSVC 7.1 emits the
// retail fully-unrolled test/jge/cmp/movsx sequence.
void __cdecl bfmeClampBlock(unsigned char *dst, short *src, int dstStride, int srcStride)
{
	int row = 8;
	do {
		short s;
		int v;

		s = src[0];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[0] = (unsigned char)v;

		s = src[1];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[1] = (unsigned char)v;

		s = src[2];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[2] = (unsigned char)v;

		s = src[3];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[3] = (unsigned char)v;

		s = src[4];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[4] = (unsigned char)v;

		s = src[5];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[5] = (unsigned char)v;

		s = src[6];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[6] = (unsigned char)v;

		s = src[7];
		if (s < 0)
			v = 0;
		else if (s > 255)
			v = 255;
		else
			v = s;
		dst[7] = (unsigned char)v;

		src += srcStride;
		dst += dstStride;
	} while (--row);
}
