// Generic scalar codec helper for dispatch-table slot 20.
//
// Retail boundary: 0x009A9550..0x009A9658 (265 bytes); INT3 padding starts
// at 0x009A9659 before the next generic slot helper at 0x009A9660.  The
// matched installer and bfmeExpand3to5Mmx sibling establish the three-argument
// cdecl source/count/destination ABI.  A three-byte source group expands to
// five bytes with the same 2/5 and 4/5 weights as the MMX path; the final group
// repeats its last source byte at the right edge.

// ?Rva009A9550@@YAXPBXHPAX@Z
void __cdecl Rva009A9550(const void *source, int bytes, void *destination)
{
	const unsigned char *src = (const unsigned char *)source;
	unsigned char *dst = (unsigned char *)destination;
	int remaining = bytes - 3;

	if (remaining != 0)
	{
		unsigned int groups = (unsigned int)(remaining - 1) / 3 + 1;
		do
		{
			unsigned int first = src[0];
			unsigned int second = src[1];
			dst[0] = (unsigned char)first;
			dst[1] = (unsigned char)((first * 102 + second * 154 + 128) >> 8);

			unsigned int third = src[2];
			dst[2] = (unsigned char)((second * 205 + third * 51 + 128) >> 8);
			dst[3] = (unsigned char)((second * 51 + third * 205 + 128) >> 8);

			unsigned int fourth = src[3];
			dst[4] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
			src += 3;
			dst += 5;
			--groups;
		}
		while (groups != 0);
	}

	unsigned int first = src[0];
	unsigned int second = src[1];
	dst[0] = (unsigned char)first;
	dst[1] = (unsigned char)((first * 102 + second * 154 + 128) >> 8);

	unsigned int third = src[2];
	dst[2] = (unsigned char)((second * 205 + third * 51 + 128) >> 8);
	dst[3] = (unsigned char)((second * 51 + third * 205 + 128) >> 8);
	dst[4] = (unsigned char)third;
}
