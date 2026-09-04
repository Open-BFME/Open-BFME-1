// ?Rva009AA8F0Dispatch@@YAXPAURva009AA8F0Context@@HPAURva009AA8F0Block@@@Z
// partial score=0.98 date=2026-09-04
// ?Rva009AA8F0Dispatch@@YAXPAURva009AA8F0Context@@HPAURva009AA8F0Block@@@Z
// Open-BFME5 conversion of the codec dispatch body at retail 0x009AA8F0.

struct Rva009AA8F0Context
{
	unsigned char m_pad0[0x08];
	void *m_ready;
	unsigned char m_pad1[0x68 - 0x0c];
	unsigned int m_mode;
	unsigned char m_pad2[0x70 - 0x6c];
	unsigned int m_height;
	unsigned int m_width;
};

struct Rva009AA8F0Block
{
	unsigned int m_width;
	unsigned int m_height;
	unsigned char m_pad0[0x0c - 0x08];
	unsigned int m_step;
};

extern void __cdecl d_009a8c50();
extern void __cdecl d_009aa4f0();

struct Rva009AA750Context;
struct Rva009AA750Block;
extern void __cdecl Rva009AA750CopyPlanes(
	Rva009AA750Context *context, int offset, Rva009AA750Block *block);

void __cdecl Rva009AA8F0Dispatch(
	Rva009AA8F0Context *context, int offset, Rva009AA8F0Block *block)
{
	if (context->m_ready != 0)
		((void (__cdecl *)(Rva009AA8F0Context *, int))d_009a8c50)(context, offset);
	if (context->m_mode > 1)
	{
		if (context->m_mode != 2)
			return;
		Rva009AA750CopyPlanes(
			(Rva009AA750Context *)context, offset, (Rva009AA750Block *)block);
		return;
	}
	unsigned int width = (block->m_height - context->m_width) >> 1;
	int halfWidth = (int)width >> 1;
	unsigned int x = (block->m_width - context->m_height) >> 1;
	int halfX = (int)x >> 1;
	int outputOffset = halfWidth * block->m_step + halfX;
	int length = (int)width * block->m_width + x;
	((void (__cdecl *)(Rva009AA8F0Context *, int, Rva009AA8F0Block *, int, int))d_009aa4f0)(
		context, offset, block, length, outputOffset);
}
