// Generic scalar counterpart of bfmeInterpRows2Mmx in dispatch slot 12.
// The matched installer caller and MMX sibling establish the three-argument
// cdecl ABI: in-place byte buffer, row stride, and byte width.

// ?Rva009A9720@@YAXPAEHI@Z
void __cdecl Rva009A9720(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;

	while (bytes > 0)
	{
		unsigned int first = cursor[0];
		unsigned int second = cursor[stride];
		cursor[stride] = (unsigned char)((first * 102 + second * 154 + 128) >> 8);

		unsigned int third = cursor[stride * 2];
		cursor[stride * 2] = (unsigned char)((second * 205 + third * 51 + 128) >> 8);
		cursor[stride * 3] = (unsigned char)((second * 51 + third * 205 + 128) >> 8);
		cursor[stride * 4] = (unsigned char)third;

		++cursor;
		--bytes;
	}
}
