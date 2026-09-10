// ?d_009b5530@@YAXXZ
// partial score=0.3 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail 0x009B5530 is the VP6 motion-compensation decision body reached by
// the decoder wrapper at 0x009B5830.  The address-derived name is deliberate:
// no source symbol, string, or vtable identifies a more specific owner.

extern void __cdecl Rva009C84D0Vp6Filter(void *, void *, int, int);
extern int __cdecl rva009C8130(const unsigned char *, int);

extern void *g_bfmeSlotB50;
extern void *g_bfmeSlotB54;

typedef void (__cdecl *Rva009B5530Blend)(
	void *, void *, int, int, int, int, int);
typedef void (__cdecl *Rva009B5530Unpack)(void *, void *, void *);

struct Rva009B5530Vp6Context
{
	unsigned char m_pad00[0x70];
	int m_stride;
	int m_horizontalStride;
	unsigned char m_pad78[4];
	int m_shift;
	int m_motionMask;
	unsigned char m_pad84[4];
	int m_scale;
	unsigned char m_pad8C[0x24C - 0x8C];
	unsigned char *m_altBase;
	unsigned char m_pad250[4];
	unsigned char *m_base;
	unsigned char m_pad258[0x290 - 0x258];
	unsigned char *m_buffer;
	unsigned char m_pad294[0x692 - 0x294];
	unsigned char m_filterMode;
	unsigned char m_filterShift;
	int m_dispersionLimit;
	unsigned char m_pad698[0x4534 - 0x698];
	unsigned char m_enabled;
};

static short rva009B5530MotionX(
	const Rva009B5530Vp6Context *context, int index)
{
	return *(const short *)((const unsigned char *)context + 0x24 + index * 4);
}

static short rva009B5530MotionY(
	const Rva009B5530Vp6Context *context, int index)
{
	return *(const short *)((const unsigned char *)context + 0x26 + index * 4);
}

static int rva009B5530Abs(int value)
{
	return value < 0 ? -value : value;
}

// ?Rva009B5530Vp6MotionCompensation@@YGXPAU1@HH@Z
void __cdecl Rva009B5530Vp6MotionCompensation(
	Rva009B5530Vp6Context *context, int sourceOffset, int motionIndex)
{
	int codecMode = *(const int *)((const unsigned char *)context + 8);
	unsigned char motionEnabled =
		*(const unsigned char *)((const unsigned char *)context + 0x19D);
	unsigned char *base = context->m_base;
	if (*(const int *)(0x00D42BA0 + codecMode * 4) == 2)
		base = context->m_altBase;

	if (!motionEnabled || !context->m_enabled)
		return;

	int motionY = rva009B5530MotionY(context, motionIndex);
	int motionX = rva009B5530MotionX(context, motionIndex);
	Rva009C84D0Vp6Filter(context, base + context->m_stride, motionX, motionY);

	int mask = context->m_motionMask;
	unsigned char *buffer = context->m_buffer;
	int sourceX = rva009B5530MotionX(context, motionIndex);
	int sourceY = rva009B5530MotionY(context, motionIndex);
	int scaledX = sourceX;
	int scaledY = sourceY;
	int horizontal = context->m_horizontalStride;

	if (*(const int *)(0x00D42BA0 + codecMode * 4) != 2) {
		scaledY = sourceY;
		if (scaledY < 0)
			scaledY = (scaledY + mask) >> context->m_shift;
		else
			scaledY >>= context->m_shift;
		scaledY *= context->m_scale;
		scaledX = sourceX;
		if (scaledX < 0)
			scaledX = (scaledX + mask) >> context->m_shift;
		else
			scaledX >>= context->m_shift;
	}

	int x = scaledX + horizontal;
	int y = scaledY + (int)base;
	int edgeX = 0;
	int edgeY = 0;
	int step = 0x10;
	int limit = 0x22;

	if (scaledX & sourceX) {
		edgeX = sourceX > 0 ? 1 : -1;
	}
	if (scaledY & sourceY) {
		edgeY = (sourceY > 0 ? 1 : -1) * step;
	}

	int destination = edgeX + edgeY;
	if (y == destination)
		return;

	if (motionIndex >= 4) {
		Rva009B5530Blend blend = (Rva009B5530Blend)g_bfmeSlotB54;
		blend((void *)(x + (int)buffer), (void *)(y + (int)buffer),
			sourceOffset, step, scaledX, scaledY, 0);
		return;
	}

	scaledX <<= 1;
	scaledY <<= 1;
	if (!motionEnabled) {
		Rva009B5530Blend blend = (Rva009B5530Blend)g_bfmeSlotB54;
		blend((void *)(x + (int)buffer), (void *)(y + (int)buffer),
			sourceOffset, step, scaledX, scaledY, 0);
		return;
	}

	int filterMode = context->m_filterMode;
	if (filterMode == 2) {
		int threshold = context->m_filterShift > 0
			? (1 << (context->m_filterShift - 1)) << 2 : 0x80;
		if (context->m_filterShift != 0
			&& rva009B5530Abs(edgeY) > threshold) {
			Rva009B5530Blend blend = (Rva009B5530Blend)g_bfmeSlotB54;
			blend((void *)(x + (int)buffer), (void *)(y + (int)buffer),
				sourceOffset, step, scaledX, scaledY, 0);
			return;
		}
		if (rva009B5530Abs(edgeX) <= threshold
			&& rva009B5530Abs(edgeY) <= threshold)
			goto measure;
	}

	{
		Rva009B5530Blend blend = (Rva009B5530Blend)g_bfmeSlotB54;
		blend((void *)(x + (int)buffer), (void *)(y + (int)buffer),
			sourceOffset, step, scaledX, scaledY, 0);
		return;
	}

measure:
	if (context->m_dispersionLimit != 0) {
		int dispersion = rva009C8130((const unsigned char *)(y + (int)buffer), step);
		Rva009B5530Blend blend = (Rva009B5530Blend)g_bfmeSlotB54;
		blend((void *)(x + (int)buffer), (void *)(y + (int)buffer),
			sourceOffset, step, scaledX, scaledY,
			dispersion >= context->m_dispersionLimit);
		return;
	}

	if (filterMode != 2) {
		Rva009B5530Blend blend = (Rva009B5530Blend)g_bfmeSlotB54;
		blend((void *)(x + (int)buffer), (void *)(y + (int)buffer),
			sourceOffset, step, scaledX, scaledY, 1);
		return;
	}

	Rva009B5530Unpack unpack = (Rva009B5530Unpack)g_bfmeSlotB50;
	unpack((void *)(y + (int)buffer), (void *)(x + (int)buffer),
		(void *)(sourceOffset + (int)buffer));
}
