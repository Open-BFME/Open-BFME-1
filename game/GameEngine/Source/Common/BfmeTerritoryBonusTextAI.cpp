// ?rva00573C20@BfmeTableAI@@QAEXHHH@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00573C20, 314 bytes (RET 0Ch at +0x137, INT3 after). Only caller:
// the score-screen body at 0x00575B70. The receiver is the BfmeTableAI whose
// bfmeNumberedAI (0x00573580, BfmeNumberedLookupAI.cpp) it calls, so the
// method keeps that owner and an address-derived name. It builds the APT key
// "APT:PointsTerritoryBonus%c%d" from a territory letter and count+1,
// translates the numbered label, prefixes L"x " when the count is one, and
// hands key and text to WindowManager::bfme_setAptText through the manager
// at VA 0x012F19E8.
// The first parameter is an int narrowed to char at the format call: a char
// parameter puts the UnicodeString and the label temporary on each other's
// dead parameter slots (13 displacement bytes).
#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const unsigned short *text);

#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


class AsciiStringAI : public AsciiString {};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};
extern WindowManager *g_rva012F19E8WindowManager;

class BfmeTableAI
{
public:
	AsciiStringAI bfmeNumberedAI(int number);
	void rva00573C20(int territory, int count, int number);
};

void BfmeTableAI::rva00573C20(int territory, int count, int number)
{
	AsciiString key;
	key.format("APT:PointsTerritoryBonus%c%d", (char)(territory + 'A'), count + 1);
	UnicodeString text;
	text.translate(bfmeNumberedAI(number));
	if (count == 1) {
		UnicodeString bonus(text);
		((StringBase<unsigned short>*)(&(text)))->set(L"x ", wcslen(L"x "));
		((StringBase<unsigned short>*)(&(text)))->concat(((StringBase<unsigned short>*)(&(bonus)))->str(), ((StringBase<unsigned short>*)(&(bonus)))->getLength());
	}
	g_rva012F19E8WindowManager->bfme_setAptText(key, text);
}
