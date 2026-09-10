// ?Rva009A9660@@YAXPAEHI@Z
// partial score=0.88 date=2026-09-10
// Generic scalar codec helper for dispatch-table slot 18.
// Retail 0x009A9660 updates four in-place rows for each byte.  The MMX
// sibling bfmeInterpRows6Mmx fixes the buffer/stride/count cdecl ABI and the
// row arrangement: the two middle outputs use the original second and third
// rows, while the trailing output uses the third and fifth rows.

// ?Rva009A9660@@YAXPAEHI@Z
void __cdecl Rva009A9660(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;
	while (bytes > 0)
	{
		unsigned char *row4 = cursor + stride * 4;
		unsigned char *row2 = cursor + stride * 2;
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
		--bytes;
	}
}
