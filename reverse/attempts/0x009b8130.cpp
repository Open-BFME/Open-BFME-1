// ?Rva009B8130Vp6Reconstruct@@YAXPAURva009B8130Vp6Context@@IIIIII@Z
// partial score=0.03 date=2026-09-02
// Partial reconstruction of the VP6 MMX block-output loop at retail 0x009B8130.
// The surrounding 0x009Bxxxx family is the bundled VP6 decoder.  This entry is
// cdecl with seven arguments and walks [firstBlock, firstBlock + blockCount).
// The retail implementation keeps a 16-byte-aligned 0x1f8-byte work area and
// performs its inverse transform and packed-byte output inline.

struct Rva009B8130Vp6Context
{
	unsigned char m_pad00[ 0x0C ];
	unsigned int m_plane;
	unsigned char m_pad10[ 0x18 ];
	unsigned int *m_accumulators;
};

extern unsigned char **g_rva009B8130PlaneRows;

void Rva009B8130Vp6Reconstruct(
	Rva009B8130Vp6Context *context,
	unsigned int sourceOffset,
	unsigned int destinationOffset,
	unsigned int sourceStride,
	unsigned int firstBlock,
	unsigned int blockCount,
	unsigned int destinationStride )
{
	__declspec(align(16)) short work[ 248 ];
	unsigned int endBlock = firstBlock + blockCount;

	for( unsigned int block = firstBlock; block < endBlock; ++block )
	{
		unsigned char *destination =
			g_rva009B8130PlaneRows[ context->m_plane ] + destinationOffset;
		unsigned int sum = 0;

		// Keep the recovered storage contract explicit.  The MMX body computes
		// 64 signed samples in this area before packing them to eight rows.
		for( unsigned int i = 0; i < 64; ++i )
		{
			short sample = work[ i ];
			int value = sample;
			if( value < 0 ) value = 0;
			if( value > 255 ) value = 255;
			destination[ ( i >> 3 ) * destinationStride + ( i & 7 ) ] =
				(unsigned char)value;
			sum += (unsigned short)sample;
		}

		context->m_accumulators[ block - 1 ] += sum;
		sourceOffset += 8;
		destinationOffset += 8;
		(void)sourceStride;
	}
}
