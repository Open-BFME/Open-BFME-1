// Generic scalar codec helper for dispatch-table slot 4.
//
// Retail boundary: 0x009A9920..0x009A9957 (56 bytes); INT3 padding starts at
// 0x009A9958 before the next helper.  The generic codec
// path averages the byte at the current position with the byte two row
// strides below it, storing the rounded result one row stride below it.  The
// slot-4 MMX sibling is bfmeAverageMmx(void *, int, int), which fixes this
// helper's three-argument cdecl buffer/stride/count ABI.

// ?Rva009A9920@@YAXPAEHI@Z
void __cdecl Rva009A9920(unsigned char *source, int stride, unsigned int count)
{
	unsigned char *cursor = source;
	while (count > 0)
	{
		unsigned int upper = cursor[0];
		unsigned int lower = cursor[stride * 2];
		cursor[stride] = (unsigned char)((upper + lower + 1) >> 1);
		++cursor;
		--count;
	}
}
