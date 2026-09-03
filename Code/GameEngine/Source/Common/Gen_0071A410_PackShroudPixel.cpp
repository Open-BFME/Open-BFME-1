// cl: /DNDEBUG /MD
//
// Retail 0x0071A410. Cdecl shroud-level pixel packer.

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

// ?packShroudPixel@@YAIE@Z
unsigned int packShroudPixel(UnsignedByte level)
{
	Real s = (Real)level;
	unsigned int b = (unsigned int)(s * TheWritableGlobalData->m_shroudColorB);
	Int g = (Int)(s * TheWritableGlobalData->m_shroudColorG);
	Int r = (Int)(s * TheWritableGlobalData->m_shroudColorR);

	Int cap = 255;
	Int v = (Int)level - 4;
	Int zero = 0;
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
