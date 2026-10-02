// cl: -Iinputs/reference/shims/stringbaseascii -Igame/Libraries/Source/WWVegas/WWLib

// The pinned empty-string literal (symbols.csv ?g_Rva0107301CEmptyString@@3QBDB,
// RVA 0x00C7301C); the census alias _bfmeInfoDND was a placeholder for it.
extern const char g_Rva0107301CEmptyString[];

// Retail 0x00213EF0 builds the string IN PLACE in the caller's buffer --
// `mov ecx, esi` then one bare thiscall constructor call -- so the callee is not
// a member of BfmeOtherDND at all: it is StringBase<char>'s const char*
// constructor, the body the ledger owns as ??0?$StringBase@D@@AAE@PBD@Z at
// 0x00888BC0 (StringBase.cpp). That constructor is private and only AsciiString
// and UnicodeString are its friends, so this spells the call the way
// inputs/reference/shims/stringbaseascii already spells it everywhere else: the
// shim's public AsciiString(const char *) is a visible delegation to
// StringBase<char>'s, so the qualified constructor call inlines away and this
// object references the retail body itself instead of a placeholder name.
// m_name's field is never used here, so the buffer stays exactly as wide as the
// pointer the argument already is.
#include "Common/AsciiString.h"

class BfmeOtherDND
{
};

class BfmeThingDND
{
public:
	BfmeOtherDND *bfmeGoDND(BfmeOtherDND *other);
};

BfmeOtherDND *BfmeThingDND::bfmeGoDND(BfmeOtherDND *other)
{
	volatile int tmp = 0;
	((AsciiString *)other)->AsciiString::AsciiString(g_Rva0107301CEmptyString);
	return other;
}