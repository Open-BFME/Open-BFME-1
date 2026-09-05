// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009ACBA0Context;
int *Rva009ACBA0SetupBounding(Rva009ACBA0Context *ctx, int flimit);

extern int *g_rva01356A9C;
extern int *(__cdecl *g_rva01356E64)(Rva009ACBA0Context *, int);
extern void (__cdecl *g_rva01356AA0)();
extern void (__cdecl *g_rva01356A98)();

struct Rva009AF320Context;
void copyPlane009AF0D0(Rva009AF320Context *, unsigned, int, unsigned, unsigned, unsigned char *, unsigned char *, void (*)());

struct Rva009AF320Context
{
	int m_mode;
	unsigned char m_pad04[8];
	int m_tableIndex;
	unsigned char m_pad10[0x28 - 0x10];
	unsigned char *m_scratch;
	unsigned char m_pad2C[0x38 - 0x2C];
	int *m_bounding;
	unsigned char m_pad3C[0x78 - 0x3C];
	unsigned char *m_planeY;
	unsigned char *m_planeU;
	unsigned char *m_planeV;
	int m_extra84;
	int m_extra88;
	unsigned m_scratchCount;
	unsigned m_width;
	unsigned m_height;
	unsigned m_strideY;
	unsigned m_strideUV;
};

void Rva009AF320CopyPlanes(Rva009AF320Context *ctx, int a, int b)
{
	int *bound;
	if (ctx->m_mode >= 2) {
		int value = g_rva01356A9C[ctx->m_tableIndex];
		bound = Rva009ACBA0SetupBounding(
			(Rva009ACBA0Context *)ctx, value);
	} else {
		int value = g_rva01356A9C[ctx->m_tableIndex];
		bound = g_rva01356E64(
			(Rva009ACBA0Context *)ctx, value);
	}

	unsigned char *saved = ctx->m_scratch;
	int aa = a;
	ctx->m_bounding = bound;
	memset(saved, 0, ctx->m_scratchCount * 4);

	copyPlane009AF0D0(
		ctx,
		ctx->m_strideY << 1,
		0,
		ctx->m_width,
		ctx->m_height >> 1,
		ctx->m_planeY + aa,
		ctx->m_planeY + b,
		g_rva01356AA0);

	{
		unsigned h = ctx->m_height;
		unsigned w = ctx->m_width;
		unsigned bytes = w * h;
		bytes = bytes / 2;
		bytes = bytes * 4;
		ctx->m_scratch += bytes;
	}

	copyPlane009AF0D0(
		ctx,
		ctx->m_strideY << 1,
		0,
		ctx->m_width,
		ctx->m_height >> 1,
		ctx->m_planeY + ctx->m_strideY + aa,
		ctx->m_planeY + ctx->m_strideY + b,
		g_rva01356AA0);

	ctx->m_scratch = saved;

	copyPlane009AF0D0(
		ctx,
		ctx->m_strideUV,
		ctx->m_extra84,
		ctx->m_width >> 1,
		ctx->m_height >> 1,
		ctx->m_planeU + aa,
		ctx->m_planeU + b,
		g_rva01356A98);

	copyPlane009AF0D0(
		ctx,
		ctx->m_strideUV,
		ctx->m_extra84 + ctx->m_extra88,
		ctx->m_width >> 1,
		ctx->m_height >> 1,
		ctx->m_planeV + aa,
		ctx->m_planeV + b,
		g_rva01356A98);
}
