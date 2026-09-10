// Generic scalar codec helper for dispatch-table slot 17.
//
// Retail boundary: 0x009A9960..0x009A997B (28 bytes).  The generic codec
// path copies each byte at the current position to the same position one
// stride later.  The slot-17 MMX sibling is bfmeCopyMmx(void *, int, int),
// which fixes this helper's three-argument cdecl ABI and buffer/stride role.

// ?Rva009A9960@@YAXPAXHI@Z
void __cdecl Rva009A9960(void *source, int stride, unsigned int count)
{
	unsigned char *cursor = (unsigned char *)source;
	while (count > 0)
	{
		unsigned char value = *cursor;
		cursor[stride] = value;
		++cursor;
		--count;
	}
}
