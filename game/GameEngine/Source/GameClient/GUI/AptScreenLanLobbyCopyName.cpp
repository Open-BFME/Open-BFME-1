// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x005171A0: copy TheLAN->GetMyName() into the output string.
// LANAPI constructor 0x006854F0 installs vtable 0x0111AF50; startup 0x004D18B0
// stores its receiver at VA0x012F7730. Slot47 (+BC) reaches GetMyName685660.
// The screen method keeps its address because the original name is unknown.

#include "unicode_string.h"
// Canonical unicode_string.cpp bodies, visible for retail inlining.
inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
	return *this;
}

class LANAPI
{
public:
#define LANAPI_SLOT(N) virtual void slot##N();
	LANAPI_SLOT(0)  LANAPI_SLOT(1)  LANAPI_SLOT(2)
	LANAPI_SLOT(3)  LANAPI_SLOT(4)  LANAPI_SLOT(5)
	LANAPI_SLOT(6)  LANAPI_SLOT(7)  LANAPI_SLOT(8)
	LANAPI_SLOT(9)  LANAPI_SLOT(10) LANAPI_SLOT(11)
	LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14)
	LANAPI_SLOT(15) LANAPI_SLOT(16) LANAPI_SLOT(17)
	LANAPI_SLOT(18) LANAPI_SLOT(19) LANAPI_SLOT(20)
	LANAPI_SLOT(21) LANAPI_SLOT(22) LANAPI_SLOT(23)
	LANAPI_SLOT(24) LANAPI_SLOT(25) LANAPI_SLOT(26)
	LANAPI_SLOT(27) LANAPI_SLOT(28) LANAPI_SLOT(29)
	LANAPI_SLOT(30) LANAPI_SLOT(31) LANAPI_SLOT(32)
	LANAPI_SLOT(33) LANAPI_SLOT(34) LANAPI_SLOT(35)
	LANAPI_SLOT(36) LANAPI_SLOT(37) LANAPI_SLOT(38)
	LANAPI_SLOT(39) LANAPI_SLOT(40) LANAPI_SLOT(41)
	LANAPI_SLOT(42) LANAPI_SLOT(43) LANAPI_SLOT(44)
	LANAPI_SLOT(45) LANAPI_SLOT(46)
#undef LANAPI_SLOT
	virtual UnicodeString GetMyName();
};

extern LANAPI *TheLAN;

class BfmeAptScreenLanLobby
{
public:
	void copyLanNameRva005171A0(UnicodeString &dest);
};

// ?copyLanNameRva005171A0@BfmeAptScreenLanLobby@@QAEXAAVUnicodeString@@@Z
void BfmeAptScreenLanLobby::copyLanNameRva005171A0(UnicodeString &dest)
{
	if (TheLAN)
		dest = TheLAN->GetMyName();
}
