// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009ACBA0Context;
int *Rva009ACBA0SetupBounding(Rva009ACBA0Context *ctx, int flimit);

extern int *g_rva01356A9C;
extern void (__cdecl *g_rva01356AA0)();
extern void (__cdecl *g_rva01356A98)();

struct Rva009AF200Context;
void copyPlane009AF0D0(Rva009AF200Context *, unsigned, int, unsigned, unsigned, unsigned char *, unsigned char *, void (*)());
void copyPlane009AEEE0(Rva009AF200Context *, int, int, int);

struct Rva009AF200Context
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
	unsigned m_scratchCount;
	unsigned m_width;
	unsigned m_height;
	unsigned m_strideY;
	unsigned m_strideUV;
};

void Rva009AF200CopyPlanes(Rva009AF200Context *ctx, int x, int y)
{
	memset(ctx->m_scratch, 0, ctx->m_scratchCount * 4);

	if (ctx->m_mode >= 2) {
		int value = g_rva01356A9C[ctx->m_tableIndex];
		ctx->m_bounding = Rva009ACBA0SetupBounding(
			(Rva009ACBA0Context *)ctx, value);
	}

	if (ctx->m_mode >= 5) {
		copyPlane009AF0D0(
			ctx,
			ctx->m_strideY,
			0,
			ctx->m_width,
			ctx->m_height,
			ctx->m_planeY + x,
			ctx->m_planeY + y,
			g_rva01356AA0);
		copyPlane009AF0D0(
			ctx,
			ctx->m_strideUV,
			0,
			ctx->m_width >> 1,
			ctx->m_height >> 1,
			ctx->m_planeU + x,
			ctx->m_planeU + y,
			g_rva01356A98);
		copyPlane009AF0D0(
			ctx,
			ctx->m_strideUV,
			0,
			ctx->m_width >> 1,
			ctx->m_height >> 1,
			ctx->m_planeV + x,
			ctx->m_planeV + y,
			g_rva01356A98);
	} else {
		copyPlane009AEEE0(ctx, x, y, 0);
		copyPlane009AEEE0(ctx, x, y, 1);
		copyPlane009AEEE0(ctx, x, y, 2);
	}
}
