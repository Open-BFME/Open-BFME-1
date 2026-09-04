// cl: /O2 /GS /MD /GR- /EHsc-

typedef unsigned long ulong;
typedef unsigned long farulong;

static void FlipBitRun(farulong *bitmap, ulong bit_addr, ulong nbits)
{
	ulong bindex;
	ulong bitnumb;

	while (nbits--)
	{
		bindex = bit_addr >> 5;
		bitnumb = bit_addr % 32;
		bitmap[bindex] ^= (1L << bitnumb);
		bit_addr++;
	}
}

void BitfieldRunAnchor(farulong *bitmap, ulong bit_addr, ulong nbits)
{
	FlipBitRun(bitmap, bit_addr, nbits);
}
