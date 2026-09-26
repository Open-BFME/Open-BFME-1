// ?bfmeBlendTileEmit@@YAXPAD0HH@Z
// partial score=0.78 date=2026-08-30
// cl: /Oy-
// Retail 0x0074A240, 91 bytes: the real body behind the blendTileData thunk.
//
// The first call widens the word at +0x00 of the info block with xor eax,eax
// followed by mov ax, which is what MSVC emits when the PARAMETER is an
// unsigned short. Declaring that parameter int gives a three-byte movzx
// instead, and the whole prologue reschedules around it.
//
// Four calls with three different conventions, and the stack cleanup is what
// separates them. The first pushes four arguments and nothing cleans them
// afterwards, so it is __stdcall. The second pushes none. The third pushes two
// and is entered with this in ecx, so it is a member. The last pushes four and
// the caller's add esp,0x10 cleans them, so it is __cdecl.
//
// The word at +0x00 of the info block is zero-extended into a full register
// before being passed, so it is an unsigned short widened to int rather than a
// short. The last call takes the third call's answer plus three, and the size
// squared.

typedef unsigned short UnsignedShort;

struct TBlendTileInfo
{
	UnsignedShort m_bfmeIndex;					// +0x00
};

extern char TheBfmeBlendBuffer[];					// 0x012F9E30
extern char TheBfmeBlendScratch[];					// 0x012FDE30

bool __stdcall bfmeBlendTileFits(UnsignedShort index, int size, char *buffer, int capacity);	// ILT 0x000274A8
void bfmeBlendTileTouch(void);						// ILT 0x0000A88F
void bfmeBlendTileEmit(char *buffer, char *scratch, int offset, int count);		// retail 0x00747940

#pragma intrinsic(_rotr)
extern "C" unsigned long _rotr(unsigned long value, int shift);

union BfmeBlendPixel
{
	unsigned long whole;
	struct
	{
		unsigned char low;
		unsigned char one;
		unsigned char two;
		unsigned char three;
	};
};

class BFMERetailWorldHeightMapBlendTileDataShim
{
public:
	void blendTileData(TBlendTileInfo *info, int size);

private:
	int bfmeBlendTileOffset(int size, TBlendTileInfo *info);	// ILT 0x0003D965
};

// ?blendTileData@BFMERetailWorldHeightMapBlendTileDataShim@@QAEXPAUTBlendTileInfo@@H@Z
void BFMERetailWorldHeightMapBlendTileDataShim::blendTileData(TBlendTileInfo *info, int size)
{
	if (bfmeBlendTileFits(info->m_bfmeIndex, size, TheBfmeBlendBuffer, 0x4000))
	{
		bfmeBlendTileTouch();

		int offset = bfmeBlendTileOffset(size, info);

		if (offset)
			bfmeBlendTileEmit(TheBfmeBlendBuffer, TheBfmeBlendScratch, offset + 3, size * size);
	}
}

void bfmeBlendTileEmit(char *buffer, char *scratch, int offset, int count)
{
	if (count > 0)
	{
		int remaining = count;
		do
		{
			unsigned long color = *(unsigned long *)buffer;
			unsigned long alpha = *(unsigned char *)offset;
			unsigned long inverse = 0xff - alpha;
			offset += 4;
			unsigned long blended = *(unsigned long *)scratch;

			unsigned long value = ((unsigned char)color * alpha
				+ (unsigned char)blended * inverse) >> 8;
			blended = (blended & 0xffffff00) | value;
			blended = _rotr(blended, 8);
			color = _rotr(color, 8);

			value = ((unsigned char)color * alpha
				+ (unsigned char)blended * inverse) >> 8;
			blended = (blended & 0xffffff00) | value;
			blended = _rotr(blended, 8);
			color = _rotr(color, 8);

			value = ((unsigned char)color * alpha
				+ (unsigned char)blended * inverse) >> 8;
			blended = (blended & 0xffffff00) | value;
			blended = _rotr(blended, 16);
			color = _rotr(color, 16);

			*(unsigned long *)scratch = blended;
			scratch += 4;
			buffer += 4;
			--remaining;
		} while (remaining != 0);
	}
}
