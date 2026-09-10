// ?copyPlane009AEEE0@@YAXPAURva009AF200Context@@HHH@Z
// partial score=0.32 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009ACBA0Context;
int *Rva009ACBA0SetupBounding(Rva009ACBA0Context *ctx, int flimit);

extern int *g_rva01356A9C;
extern void (__cdecl *g_rva01356AA0)();
extern void (__cdecl *g_rva01356A98)();
extern void (__cdecl *g_rva01356A88)();

struct Rva009AF200Context;
void copyPlane009AF0D0(Rva009AF200Context *, unsigned, int, unsigned, unsigned, unsigned char *, unsigned char *, void (*)());

typedef void (__cdecl *Rva009AEEE0Operation)(
	Rva009AF200Context *, unsigned char *, unsigned char *, unsigned,
	unsigned, unsigned, void (__cdecl *)());

extern Rva009AEEE0Operation g_rva01356E94;
extern Rva009AEEE0Operation g_rva01356E88;

void __cdecl Rva009AD750(
	Rva009AF200Context *, unsigned char *, unsigned char *, unsigned,
	unsigned, unsigned, void (__cdecl *)());
void __cdecl Rva009ACC80(
	Rva009AF200Context *, unsigned char *, unsigned char *, unsigned,
	unsigned, unsigned, void (__cdecl *)());

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
	unsigned m_extra84;
	unsigned m_extra88;
	unsigned m_scratchCount;
	unsigned m_width;
	unsigned m_height;
	unsigned m_strideY;
	unsigned m_strideUV;
};

void copyPlane009AEEE0(Rva009AF200Context *ctx, int x, int y, int plane)
{
	Rva009AF200Context *self = ctx;
	int mode = self->m_mode;
	unsigned sourceOffset = 0;
	void (__cdecl *callback)() = 0;
	Rva009AEEE0Operation operation;
	Rva009AEEE0Operation finalOperation;
	unsigned char *base;
	unsigned width;
	unsigned height;
	unsigned stride;
	unsigned char *source;
	unsigned char *destination;
	int delta;
	unsigned char *row;
	unsigned rows;

	if (mode >= 2) {
		operation = g_rva01356E94;
		finalOperation = Rva009AD750;
	} else {
		operation = g_rva01356E88;
		finalOperation = Rva009ACC80;
	}

	int selector = plane - sourceOffset;
	if (selector == 0) {
		width = self->m_width;
		stride = self->m_strideY;
		base = self->m_planeY;
		height = self->m_height;
	} else {
		stride = self->m_strideUV;
		--selector;
		width = self->m_width >> 1;
		if (selector == 0) {
			sourceOffset = self->m_extra84;
			base = self->m_planeU;
		} else {
			sourceOffset = self->m_extra84 + self->m_extra88;
			base = self->m_planeV;
		}
		height = self->m_height >> 1;
	}

	if (mode >= 2) {
		if (plane == 0) {
			callback = g_rva01356AA0;
		} else if (plane == 1 || plane == 2) {
			callback = g_rva01356A98;
		}
	} else {
		callback = g_rva01356A88;
	}

	source = base + x;
	destination = base + y;
	delta = (int)(source - destination);
	row = destination;
	rows = 4;
	while (rows != 0) {
		unsigned char *cursor = row;
		unsigned bytes = stride;
		while (bytes != 0) {
			*cursor = cursor[delta];
			++cursor;
			--bytes;
		}
		row += stride;
		--rows;
	}

	if (height > 1) {
		unsigned count = height - 1;
		unsigned char *callbackSource = source + stride * 8;
		unsigned char *callbackDestination = destination + stride * 8;
		do {
			operation(
				self, callbackSource, callbackDestination, stride, width,
				sourceOffset, callback);
			sourceOffset += width;
			--count;
		} while (count != 0);
	}

	row = destination + stride * 4;
	rows = 4;
	while (rows != 0) {
		unsigned char *cursor = row;
		unsigned bytes = stride;
		while (bytes != 0) {
			*cursor = cursor[delta];
			++cursor;
			--bytes;
		}
		row += stride;
		--rows;
	}

	finalOperation(
		self, source, destination, stride, width, sourceOffset, callback);
}

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
