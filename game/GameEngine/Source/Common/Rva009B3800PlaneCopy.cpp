// ?Rva009B3800PlaneCopy@@YAXPAURva009B3800Context@@HH@Z
// Retail 0x009B3800 (503 bytes): three-plane VP6 copy/filter helper.
//
// Reached only from the anonymous VP6 grid driver at 0x009A6130 (2 sites).
// Identity is not recovered beyond the codec role, so the function and the
// context keep the retail address token rather than claiming a class name.
// The context offsets are the plane layout already witnessed by the landed
// siblings Rva009AF200CopyPlanes.cpp and Rva009AF320CopyPlanes.cpp
// (m_mode 0x00, m_tableIndex 0x0C, m_planeY/U/V 0x78/0x7C/0x80,
// m_width 0x90, m_height 0x94, m_strideY 0x98, m_strideUV 0x9C).
//
// All seven relocations are DIR32 data references (the two bounding tables and
// the three indirect callback slots); there are no direct calls and no pins.
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
	unsigned char *base = 0;
	int firstCount = (int)ctx->m_width;
	int secondCount = (int)ctx->m_height;
	int plane;
	int *bounding;
	unsigned int stride = 0;
	int mode = ctx->m_mode;
	int tableIndex = ctx->m_tableIndex;
	int selector;

	if (mode >= 2)
		selector = g_rva01356A9C[tableIndex];
	else
		selector = g_rva011428E8[tableIndex];

	bounding = g_rva01356E64(ctx, selector);

	plane = 0;
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

		unsigned char *dest = base + destinationOffset;
		memcpy(dest, base + sourceOffset, stride * 8);

		if (firstCount > 1)
		{
			unsigned char *cursor = dest + 6;
			int count = firstCount - 1;
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
				unsigned char *rowDest = base + destinationOffset;
				memcpy(rowDest, base + sourceOffset, stride * 8);
				g_rva01356EC4(ctx, rowDest, stride, bounding);

				if (firstCount > 1)
				{
					unsigned char *cursor = rowDest + 8;
					int count = firstCount - 1;
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
