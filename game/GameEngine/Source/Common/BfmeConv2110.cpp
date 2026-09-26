// cl: /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

struct BfmeKeyZP
{
	char m_bfmeFlagZP;
	unsigned char m_bfmePadZP[3];
	AsciiString m_bfmeNameZP;
};

char __stdcall bfmeLessZP(const BfmeKeyZP *a, const BfmeKeyZP *b);

char __stdcall bfmeLessZP(const BfmeKeyZP *a, const BfmeKeyZP *b)
{
	char c = a->m_bfmeFlagZP;

	if ((b->m_bfmeFlagZP == 0) ^ (c == 0))
		return c;

	return a->m_bfmeNameZP.compareNoCase(b->m_bfmeNameZP) < 0;
}
