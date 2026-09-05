// ?refreshCells@Rva006C23B0@@QAEXHH@Z
// partial score=0.1 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// ?d_006c23b0@@YAXXZ (Code/gen_asm/d_0069c4f0.asm), size 690.
//
// RVA-derived reconstruction, identity NOT proven. `this` is believed to be
// W3DRadar (neighbours 0x006C2710 setShroudLevel / 0x006C3170 drawEvents are
// both W3DRadar; the naked lift at 0x006C2710 also reads [g_bfmeA1087+0x30b8]
// -- the SAME global+offset this body reads -- so both are W3DRadar methods
// gated on the same "shroud enabled" pointer). Embedded sub-object at
// this+0x1494 answers getSurfaceLevel/bfmeAskGN/bfmeAskEF -- looks like a
// W3DRadarResetTexture member (matches the pinned getSurfaceLevel call).
//
// Structural notes for the next worker:
//   Two int stack args (ret 0xc pops 3 dwords total incl. one more) define a
//   world-space rect; getSurfaceLevel() fills a local W3DRadarResetSurface
//   with per-axis scale/offset floats (+0x10/+0x14 read as floats). Those,
//   combined with __ftol2-heavy fixed-point math and bfmeAskGN/bfmeAskEF
//   (BfmeThingGN/BfmeThingEF, both returning an int bias added before the
//   final ftol2), produce a 2D cell bounding box [minX..maxX]x[minY..maxY]
//   clamped to [0,0x80). It then double-loops the box calling the
//   still-dumped 0x008FCF40 (690B, unexplored) per cell with (row, col,
//   &localSurface). At the end it destructs the local W3DRadarResetSurface
//   (target 0x0090E670's sibling dtor at 0x0090C5B0) and calls a global
//   bfmeUnlock1179 (target 0x00D05B10) -- a shroud-buffer lock/unlock pair
//   opened only when the this+0x30b8-style global pointer is non-null.
//
// Not byte-matched: this is a compiling skeleton only, banked as partial.
// The exact float expression order (fmul/fild/ftol2 sequencing) was not
// reproduced -- see docs/shape_levers.md x87 reassociation notes before the
// next attempt.

struct Rva006C23B0Surface
{
	unsigned char m_pad[0x10];
	float m_scaleX;
	float m_scaleY;
	unsigned char m_tail[0x24];
};

class Rva006C23B0SubTexture
{
public:
	Rva006C23B0Surface getSurfaceLevel();
	int bfmeAskGN();
	int bfmeAskEF();
};

extern void W3DRadarResetLock(void);
extern int __ftol2(void);
extern void j_00026099(void);
extern void j_0000827e(void);

class Rva006C23B0
{
public:
	void refreshCells(int arg1, int arg2);

private:
	unsigned char m_pad[0x1494];
	Rva006C23B0SubTexture m_texture;
};

extern void *g_bfmeA1087;

void Rva006C23B0::refreshCells(int arg1, int arg2)
{
	void *shroud = *(void **)((char *)g_bfmeA1087 + 0x30b8);
	if (shroud == 0)
		return;

	W3DRadarResetLock();

	Rva006C23B0Surface surface = m_texture.getSurfaceLevel();

	float sx = surface.m_scaleX;
	float sy = surface.m_scaleY;

	int minX = (int)(sx * (float)arg1);
	int maxX = (int)(sx * (float)(arg1 + 1));
	int minY = (int)(sy * (float)arg2);
	int maxY = (int)(sy * (float)(arg2 + 1));

	int bias1 = m_texture.bfmeAskGN();
	if (bias1 < 0)
		minX += bias1;

	int bias2 = m_texture.bfmeAskEF();
	if (bias2 < 0)
		minY += bias2;

	if (maxX > 0x80)
		maxX = 0x80;
	if (maxY > 0x80)
		maxY = 0x80;
	if (minX < 0)
		minX = 0;
	if (minY < 0)
		minY = 0;

	extern void refreshCell(int, int, Rva006C23B0Surface *);
	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			if (x < 0 || y < 0 || x >= 0x80 || y >= 0x80)
				continue;
			refreshCell(x, y, &surface);
		}
	}

	extern void bfmeUnlock1179(void);
	bfmeUnlock1179();
}
