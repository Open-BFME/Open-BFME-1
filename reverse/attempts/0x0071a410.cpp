// ?packShroudPixel@@YAIE@Z
// partial score=0.62 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x0071A410. Cdecl helper jumped to from ILT 0x6C2B. Scales the
// shroud-color floats at GlobalData+0xC78 by the level, builds a (level-4)
// nibble, and packs high nibbles. Level 255 forces every channel to 255.

typedef float Real;
typedef int Int;
typedef unsigned char UnsignedByte;

class GlobalData
{
public:
	char m_pad[0xc78];
	Real m_shroudColorR;
	Real m_shroudColorG;
	Real m_shroudColorB;
};

extern GlobalData *TheWritableGlobalData;

unsigned int packShroudPixel(UnsignedByte level)
{
	GlobalData &gd = *TheWritableGlobalData;
	Real s = (Real)level;
	Int b = (Int)(s * gd.m_shroudColorB);
	Int g = (Int)(s * gd.m_shroudColorG);
	Int r = (Int)(s * gd.m_shroudColorR);

	Int v = (Int)level - 4;
	Int zero = 0;
	Int cap = 255;
	Int *p = (v > 0) ? &v : &zero;
	Int t = *p * 255 / 46;
	p = (t < 255) ? &t : &cap;
	Int q = *p;

	if (level == 255)
	{
		r = 255;
		g = 255;
		b = 255;
		q = 255;
	}

	return ((q & 0xf0) << 8) | ((r & 0xf0) << 4) | ((b >> 4) & 0xf) | (g & 0xf0);
}
