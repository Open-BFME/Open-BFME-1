// ?d_009aa4f0@@YAXXZ
// partial score=0.292079 date=2026-09-23
// ?Rva009AA4F0ScalePlanes@@YAPAURva009AA4F0Block@@PAURva009AA4F0Context@@HPAU1@HH@Z

struct Rva009AA260Context
{
	unsigned char m_pad00[0x58];
	int m_hscale;
	int m_hratio;
	int m_vscale;
	int m_vratio;
};

struct Rva009AA4F0Context
{
	unsigned char m_pad00[0x40];
	unsigned int m_bytes;
	unsigned char m_pad44[0x14];
	int m_hscale;
	int m_hratio;
	int m_vscale;
	int m_vratio;
	unsigned char m_pad68[8];
	unsigned int m_height;
	unsigned int m_width;
	unsigned char *m_source0;
	unsigned char *m_source1;
	unsigned char *m_source2;
	unsigned char m_pad84[0x30];
	unsigned int m_atB4;
};

struct Rva009AA4F0Block
{
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_at08;
	unsigned int m_at0C;
	unsigned char m_pad10[4];
	unsigned int m_at14;
	unsigned char *m_at18;
	unsigned char *m_at1C;
	unsigned char *m_at20;
};

extern int __cdecl Rva009AA260Scale(
	Rva009AA260Context *, const unsigned char *, int, unsigned int,
	unsigned int, unsigned char *, unsigned int, unsigned int, unsigned int);
extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

static int Rva009AA4F0Align(
	unsigned int dimension, int scale, int ratio)
{
	if (ratio == 3)
		return (((int)(dimension + 2) / 3 * scale) * 3) / ratio;
	return (((int)(dimension + 7) / 8 * 8 * scale) / ratio);
}

Rva009AA4F0Block *__cdecl Rva009AA4F0ScalePlanes(
	Rva009AA4F0Context *context, int offset, Rva009AA4F0Block *block,
	int lumaOffset, int chromaOffset)
{
	int hratio = context->m_hratio;
	unsigned int height = context->m_height;
	int hscale = context->m_hscale;
	unsigned int scaledHeight =
		(height * hratio + hscale - 1) / hscale;
	int vscale = context->m_vscale;
	unsigned int width = context->m_width;
	unsigned int scaledWidth =
		(width * context->m_vratio + vscale - 1) / vscale;
	int alignedHeight = Rva009AA4F0Align(
		scaledHeight, hscale, hratio);
	int alignedWidth = Rva009AA4F0Align(
		scaledWidth, vscale, context->m_vratio);

	int scaleResult = Rva009AA260Scale(
		(Rva009AA260Context *)context,
		context->m_source0 + offset,
		context->m_bytes + context->m_atB4 * 2,
		scaledHeight, height,
		block->m_at18 + lumaOffset, block->m_at08,
		scaledWidth, width);

	for (int row = 0; row < alignedWidth; ++row)
		memset(block->m_at18 + lumaOffset + height +
			row * block->m_at08,
			0, alignedHeight - height);

	for (int row = width; row < alignedWidth; ++row)
		memset(block->m_at18 + lumaOffset + row * block->m_at08,
			0, alignedHeight);

	if (scaleResult == 0)
		return 0;

	Rva009AA260Scale(
		(Rva009AA260Context *)context,
		context->m_source1 + offset,
		(context->m_bytes >> 1) + context->m_atB4,
		(scaledHeight + 1) >> 1, (scaledWidth + 1) >> 1,
		block->m_at1C + chromaOffset, block->m_at14,
		(height + 1) >> 1, (width + 1) >> 1);
	Rva009AA260Scale(
		(Rva009AA260Context *)context,
		context->m_source2 + offset,
		(context->m_bytes >> 1) + context->m_atB4,
		(scaledHeight + 1) >> 1, (scaledWidth + 1) >> 1,
		block->m_at20 + chromaOffset, block->m_at14,
		(height + 1) >> 1, (width + 1) >> 1);
	return block;
}
