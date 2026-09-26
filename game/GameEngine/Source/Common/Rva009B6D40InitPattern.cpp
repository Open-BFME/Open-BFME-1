// Retail 0x009B6D40.  The codec installer places this two-argument helper in
// dispatch slot 1 for both the SSE and MMX tiers.  Its target buffer is the
// 32-byte-aligned block at context+0x3c plus 0x400; the six stores are the
// scalar pattern used by the corresponding image-filter path.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B6D40Context
{
	unsigned char m_pad0[0x3c];
	unsigned int m_patternBlock;
};

int * __cdecl Rva009B6D40(Rva009B6D40Context *context, int value)
{
	unsigned int repeated = (unsigned int)value * 0x10001u;
	unsigned int *block = (unsigned int *)((context->m_patternBlock + 0x400) & ~31u);

	block[1] = repeated;
	block[0] = repeated;
	block[3] = 0x10001u;
	block[2] = 0x10001u;
	block[5] = 0x40004u;
	block[4] = 0x40004u;
	return (int *)block;
}
