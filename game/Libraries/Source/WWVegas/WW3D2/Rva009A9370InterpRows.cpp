// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x009A9370: scalar four-row interpolation sibling of MMX interpolator.
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
		fourth = cursor[stride * 3];
		third = cursor[stride * 2];
		cursor[stride * 2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
		cursor[stride * 3] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
		cursor[stride * 4] = (unsigned char)fourth;
		++cursor;
		--bytes;
	}
}
