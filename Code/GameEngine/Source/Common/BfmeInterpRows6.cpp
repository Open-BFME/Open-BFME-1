// Generic scalar counterpart of bfmeInterpRows6Mmx in dispatch slot 18.
// The matched codec installer and MMX sibling establish the three-argument
// cdecl ABI: in-place byte buffer, row stride, and byte width.

// ?Rva009A9660@@YAXPAEHI@Z
void __cdecl Rva009A9660(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;

	for (; bytes > 0; --bytes)
	{
		unsigned char *row2 = cursor + stride * 2;
		unsigned char *row4 = cursor + stride * 4;
		unsigned int row1Value = cursor[stride];
		unsigned int row0Value = cursor[0];
		cursor[stride] = (unsigned char)((row0Value * 102 + row1Value * 154 + 128) >> 8);

		unsigned int row2Value = row2[0];
		row2[0] = (unsigned char)((row1Value * 205 + row2Value * 51 + 128) >> 8);
		row2[stride] = (unsigned char)((row1Value * 51 + row2Value * 205 + 128) >> 8);

		unsigned int row5Value = row4[stride];
		row4[0] = (unsigned char)((row2Value * 154 + row5Value * 102 + 128) >> 8);

		++cursor;
		++row2;
		++row4;
	}
}
