// ?Rva009A91D0@@YAXPBXHPAX@Z
// partial score=0.93 date=2026-09-10
// Generic scalar codec helper for the dispatch-table outlier slot.
//
// Retail boundary: 0x009A91D0..0x009A92C6 (247 bytes); INT3 padding starts
// at 0x009A92C7 before the next generic slot helper at 0x009A92D0.  The
// matched installer and bfmeExpand4to5Mmx sibling establish the
// three-argument cdecl source/count/destination ABI.  Four source bytes are
// expanded to five output bytes with the VP6 1/5, 2/5, 3/5, and 4/5 weights;
// the final group copies its last source byte at the right edge.

// ?Rva009A91D0@@YAXPBXHPAX@Z
void __cdecl Rva009A91D0(const void *source, int bytes, void *destination)
{
	unsigned char *dst = (unsigned char *)destination;
	const unsigned char *src = (const unsigned char *)source;
	int remaining = bytes - 4;

	if (remaining != 0)
	{
		unsigned int groups = (unsigned int)(remaining - 1) / 4 + 1;
		do
		{
			unsigned int first = src[0];
			unsigned int second = src[1];
			dst[0] = (unsigned char)first;
			dst[1] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

			unsigned int third = src[2];
			unsigned int fourth = src[3];
			dst[2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
			dst[3] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);

			unsigned int fifth = src[4];
			dst[4] = (unsigned char)((fourth * 205 + fifth * 51 + 128) >> 8);
			src += 4;
			dst += 5;
			--groups;
		}
		while (groups != 0);
	}

	unsigned int first = src[0];
	unsigned int second = src[1];
	dst[0] = (unsigned char)first;
	dst[1] = (unsigned char)((first * 51 + second * 205 + 128) >> 8);

	unsigned int third = src[2];
	unsigned int fourth = src[3];
	dst[2] = (unsigned char)((second * 102 + third * 154 + 128) >> 8);
	dst[3] = (unsigned char)((third * 154 + fourth * 102 + 128) >> 8);
	dst[4] = (unsigned char)fourth;
}
