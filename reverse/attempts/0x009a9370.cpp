// ?Rva009A9370@@YAXPAEHI@Z
// partial score=0.6 date=2026-09-10
// Generic scalar counterpart of bfmeInterpRowsMmx in dispatch slot 6.
// The matched installer caller and MMX sibling establish the three-argument
// cdecl ABI: in-place byte buffer, row stride, and byte width.

// ?Rva009A9370@@YAXPAEHI@Z
void __cdecl Rva009A9370(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;
	unsigned char *row3 = cursor + stride * 2;
	row3 += stride;

	while (bytes > 0)
	{
		unsigned int second = cursor[stride];
		unsigned int first = cursor[0];
		cursor[stride] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

		unsigned int third = cursor[stride * 2];
		unsigned int fourth = row3[0];
		cursor[stride * 2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
		row3[0] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
		row3[stride] = (unsigned char)fourth;

		++cursor;
		++row3;
		--bytes;
	}
}
