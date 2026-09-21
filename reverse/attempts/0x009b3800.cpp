// ?Rva009B3800PlaneCopy@@YAXPAURva009B3800Context@@HH@Z
// partial score=0.94 date=2026-09-17
// Retail 0x009B3800: three-plane VP6 copy/filter helper.
//
// The routine is reached by the anonymous VP6 grid driver at 0x009A6130.
// Its identity is not recovered beyond the codec role, so the source and
// function name retain the retail address rather than claiming a class.
// The context offsets are the same plane layout witnessed by the adjacent
// Rva009AF200/Rva009AF320 drivers.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct Rva009B3800Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x28 - 0x10];
	void *m_scratch;
	unsigned char m_pad2C[0x38 - 0x2C];
	int *m_bounding;
	unsigned char m_pad3C[0x78 - 0x3C];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	unsigned char m_pad84[0x8C - 0x84];
	unsigned int m_scratchCount;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_strideY;
	unsigned int m_strideUV;
};

typedef int *(__cdecl *Rva009B3800Setup)(Rva009B3800Context *, int);
typedef void (__cdecl *Rva009B3800Filter)(
	Rva009B3800Context *, unsigned char *, unsigned int, int *);

extern int *g_rva01356A9C;
extern int g_rva011428E8[];
extern Rva009B3800Setup g_rva01356E64;
extern Rva009B3800Filter g_rva01356E84;
extern Rva009B3800Filter g_rva01356EC4;

void __cdecl Rva009B3800PlaneCopy(
	Rva009B3800Context *ctx, int sourceOffset, int destinationOffset)
{
	int secondCount;
	int firstCount;
	int plane = 0;
	int *bounding;
	unsigned char *base;
	unsigned int stride;
	secondCount = (int)ctx->m_height;
	firstCount = (int)ctx->m_width;

	if (ctx->m_mode >= 2)
		bounding = g_rva01356E64(ctx, g_rva01356A9C[ctx->m_tableIndex]);
	else
		bounding = g_rva01356E64(ctx, g_rva011428E8[ctx->m_tableIndex]);

	do
	{
		switch (plane)
		{
		case 0:
			firstCount = (int)ctx->m_width;
			secondCount = (int)ctx->m_height;
			stride = ctx->m_strideY;
			base = ctx->m_planeY;
			break;
		case 1:
			firstCount = (int)(ctx->m_width >> 1);
			secondCount = (int)(ctx->m_height >> 1);
			stride = ctx->m_strideUV;
			base = ctx->m_planeU;
			break;
		case 2:
			firstCount = (int)(ctx->m_width >> 1);
			secondCount = (int)(ctx->m_height >> 1);
			stride = ctx->m_strideUV;
			base = ctx->m_planeV;
			break;
		}

		memcpy(base + destinationOffset, base + sourceOffset, stride * 8);

		if (firstCount > 1)
		{
			int count = firstCount - 1;
			unsigned char *cursor = base + destinationOffset + 6;
			do
			{
				g_rva01356E84(ctx, cursor, stride, bounding);
				cursor += 8;
				--count;
			}
			while (count != 0);
		}

		base = base + stride * 8;

		if (secondCount > 1)
		{
			int rows = secondCount - 1;
			do
			{
				memcpy(base + destinationOffset, base + sourceOffset, stride * 8);
				g_rva01356EC4(ctx, base + destinationOffset, stride, bounding);

				if (firstCount > 1)
				{
					int count = firstCount - 1;
					unsigned char *cursor = base + destinationOffset + 8;
					do
					{
						g_rva01356E84(ctx, cursor - 2, stride, bounding);
						g_rva01356EC4(ctx, cursor, stride, bounding);
						cursor += 8;
						--count;
					}
					while (count != 0);
				}

				base = base + stride * 8;
				--rows;
			}
			while (rows != 0);
		}

		++plane;
	}
	while (plane < 3);
}
