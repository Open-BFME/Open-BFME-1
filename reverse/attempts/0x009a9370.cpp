// ?Rva009A9370@@YAXPAEHI@Z
// partial score=0.9 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Generic scalar counterpart of the matched MMX four-row interpolator in
// dispatch slot 6.  The installer and MMX sibling establish the cdecl ABI:
// source rows, signed row stride, and unsigned byte count.
// Retail boundary: 0x009A9370..0x009A93F1 (130 bytes); INT3 padding starts at
// 0x009A93F2 and the next body starts at 0x009A9400.

// ?Rva009A9370@@YAXPAEHI@Z
void __cdecl Rva009A9370(unsigned char *source, int stride, unsigned int bytes)
{
	unsigned char *cursor = source;

	while (bytes > 0)
	{
		unsigned int second = cursor[stride];
		unsigned int first = cursor[0];
		unsigned int firstWeight = first * 51;
		unsigned int secondWeight = second * 205;
		cursor[stride] = (unsigned char)((firstWeight + secondWeight + 128) >> 8);

		unsigned int fourth;
		unsigned int third;
		third = cursor[stride * 2];
		fourth = cursor[stride * 3];
		cursor[stride * 2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
		cursor[stride * 3] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
		cursor[stride * 4] = (unsigned char)fourth;

		++cursor;
		--bytes;
	}
}
