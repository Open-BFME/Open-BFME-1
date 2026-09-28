// ?d_009b5530@@YAXXZ
// partial score=0.3125 date=2026-09-28
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// VP6 motion-compensated block prediction, retail [0x009B5530, 0x009B5830).
//
// Identity: the matched VP6 block reconstruction at 0x009B5830 calls this body
// as Rva009B5530Prepare(state, coefficients, block) before its inverse
// transform slot; the name stays address-derived because no string or symbol
// names it. The logic is On2's filtered prediction (the shape FFmpeg later
// reimplemented as vp56_mc + vp6_filter), read from the retail body:
//  * the reference plane is +0x254, or +0x24C when the mode's entry in the
//    0x01142BA0 table is 2;
//  * with deblocking on (+0x19D and +0x4534) the loop filter 0x009C84D0 copies
//    the block into the 16-byte-stride edge buffer at +0x290 (offset 2*16+2);
//    otherwise the source is the reference plus the whole-pel motion;
//  * the fractional motion picks a second source offset; when there is none
//    the block is copied through slot 0x01356B50, otherwise slot 0x01356B54
//    blends the two sources, with the four-tap choice from the filter mode
//    (+0x692), the maximum vector length (+0x693) and the block variance
//    threshold (+0x694, variance from 0x009C8130).

#include <stdlib.h>

struct Rva009B5530MotionVector
{
	short x;
	short y;
};

struct Rva009C84D0Vp6Context;

struct Rva009B5830State
{
	unsigned char pad0[8];
	int mode;											// +0x08
	unsigned char padC[0x24 - 0x0c];
	Rva009B5530MotionVector motion[6];					// +0x24
	unsigned char pad3C[0x70 - 0x3c];
	int baseOffset;										// +0x70
	int stride;											// +0x74
	unsigned char pad78[4];
	int motionShift;									// +0x7C
	int motionMask;										// +0x80
	unsigned char pad84[4];
	int motionPitch;									// +0x88
	unsigned char pad8C[0x19d - 0x8c];
	unsigned char deblock19D;							// +0x19D
	unsigned char pad19E[0x24c - 0x19e];
	unsigned char *predictionB;							// +0x24C
	unsigned char pad250[4];
	unsigned char *predictionC;							// +0x254
	unsigned char pad258[0x290 - 0x258];
	unsigned char *edgeBuffer;							// +0x290
	unsigned char pad294[0x692 - 0x294];
	unsigned char filterMode;							// +0x692
	unsigned char maxVectorBits;						// +0x693
	unsigned int varianceThreshold;						// +0x694
	unsigned char pad698[0x4534 - 0x698];
	unsigned char deblock4534;							// +0x4534
};

// A four-byte-stride table; the ledger pins it with 16-bit elements.
extern const unsigned short Rva01142BA0Table[];

extern void Rva009C84D0Vp6Filter(Rva009C84D0Vp6Context *context, void *source, int x, int y);
extern int rva009C8130(const unsigned char *block, int stride);

extern void *g_bfmeSlotB50;
extern void *g_bfmeSlotB54;

typedef void (__cdecl *Rva009B5530Copy)(unsigned char *source, void *destination, int stride);
typedef void (__cdecl *Rva009B5530Blend)(unsigned char *source1, unsigned char *source2,
	void *destination, int stride, int x8, int y8, int filter4);

void __cdecl Rva009B5530Prepare(Rva009B5830State *state, void *destination, int block)
{
	unsigned char *reference = state->predictionC;
	int mask = state->motionMask;
	if (*(const int *)&Rva01142BA0Table[state->mode * 2] == 2)
		reference = state->predictionB;

	short mvx;
	short mvy;
	int x;
	int y;
	unsigned char *source;
	int stride;
	int offset1;
	int offset2;
	int x8;
	int y8;
	if (state->deblock19D && state->deblock4534)
	{
		Rva009C84D0Vp6Filter((Rva009C84D0Vp6Context *)state, reference + state->baseOffset,
			state->motion[block].x, state->motion[block].y);
		source = state->edgeBuffer;
		mvx = state->motion[block].x;
		mvy = state->motion[block].y;
		x = mvx;
		y = mvy;
		x8 = x & state->motionMask;
		y8 = y & state->motionMask;
		stride = 16;
		offset1 = offset2 = 2 * 16 + 2;
	}
	else
	{
		mvx = state->motion[block].x;
		mvy = state->motion[block].y;
		x = mvx;
		y = mvy;
		int dy = (y + ((y >> 31) & mask)) >> state->motionShift;
		int dx = (x + ((x >> 31) & mask)) >> state->motionShift;
		y8 = y & mask;
		x8 = x & mask;
		source = reference + state->baseOffset + dy * state->motionPitch + dx;
		stride = state->stride;
		offset1 = 0;
		offset2 = 0;
	}

	if (x8)
		offset2 += (mvx > 0) * 2 - 1;
	if (y8)
		offset2 += ((mvy > 0) * 2 - 1) * stride;

	if (offset1 != offset2)
	{
		if (block < 4)
		{
			x8 <<= 1;
			y8 <<= 1;
		}
		if (block >= 4 || !state->deblock19D)
		{
			((Rva009B5530Blend)g_bfmeSlotB54)(source + offset1, source + offset2,
				destination, stride, x8, y8, 0);
		}
		else if (state->filterMode == 2)
		{
			unsigned int maxLength = state->maxVectorBits ? (1 << (state->maxVectorBits - 1)) << 2 : 0x80;
			if (state->maxVectorBits
				&& ((unsigned int)abs(x) > maxLength || (unsigned int)abs(y) > maxLength))
			{
				((Rva009B5530Blend)g_bfmeSlotB54)(source + offset1, source + offset2,
					destination, stride, x8, y8, 0);
			}
			else if (state->varianceThreshold)
			{
				((Rva009B5530Blend)g_bfmeSlotB54)(source + offset1, source + offset2,
					destination, stride, x8, y8,
					rva009C8130(source + offset1, stride) >= state->varianceThreshold);
			}
			else
			{
				((Rva009B5530Blend)g_bfmeSlotB54)(source + offset1, source + offset2,
					destination, stride, x8, y8, 1);
			}
		}
		else
		{
			((Rva009B5530Blend)g_bfmeSlotB54)(source + offset1, source + offset2,
				destination, stride, x8, y8, state->filterMode == 1);
		}
	}
	else
	{
		((Rva009B5530Copy)g_bfmeSlotB50)(source + offset1, destination, stride);
	}
}
