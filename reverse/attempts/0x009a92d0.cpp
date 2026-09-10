// ?Rva009A92D0@@YAXPAEHI@Z
// partial score=0.9 date=2026-09-10
// Complete clean reconstruction banked after a 157-byte near miss.  The
// dispatch installer and bfmeInterpRows5Mmx establish the three-argument
// cdecl ABI and the five-row interpolation family.
void __cdecl Rva009A92D0(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *row3 = source + stride * 2;
	row3 += stride;

	while (bytes > 0)
	{
		unsigned int second = source[stride];
		unsigned int first = source[0];
		source[stride] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

		unsigned int third = source[stride * 2];
		unsigned int fourth = row3[0];
		source[stride * 2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
		row3[0] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);

		row3[stride] = (unsigned char)((fourth * 205 + source[stride * 5] * 51 + 128) >> 8);

		++source;
		++row3;
		--bytes;
	}
}
