// cl: /O2 /GR- /EHsc- /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// The parse helper retail calls here is INI::parseAsciiString (0x00851EE0); the
// call goes through the real header rather than a TU-local stand-in name that
// nothing defines.
#include "Common/INI/INI.h"

struct BfmeEntryYW
{
	unsigned char m_bfmeHeadYW[0x1c];
	unsigned char m_bfmeFieldYW[8];
};

struct BfmeVecYW
{
	unsigned char m_bfmeHeadYW[0x2c];
	BfmeEntryYW *m_bfmeBeginYW;
	BfmeEntryYW *volatile m_bfmeEndYW;
};

void __cdecl bfmeParseYW(void *ini, void *inst, BfmeVecYW *store)
{
	if (store->m_bfmeEndYW - store->m_bfmeBeginYW != 0)
		INI::parseAsciiString((INI*)ini, inst, store->m_bfmeEndYW[-1].m_bfmeFieldYW, 0);
}
