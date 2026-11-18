// ?bfmeRva00467F20@WindowManager@@QAE_NH@Z
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00467F20, 293 bytes (RET 4 at +0x4C and +0x122, INT3 after).
// Sole caller: matched WindowManager::update 0x0046E850 calls it through ILT
// 0x0001DE9E for each of the twelve +0xA8 APT window records whose +0x10 bit 0
// is set (WindowManager_update.cpp), so the receiver is WindowManager. The
// method name is unproven and keeps the address. Retail returns a Bool
// (XOR AL,AL on rejection, MOV AL,1 on success); the caller discards it.
// The body reloads a pending record: it strips the extension from the
// record's path (StringBase<char>::find('.') then removeLastChar per
// character), formats "/_level%d" with the record index, hands both to
// bfmeApplyESP 0x00891E70 and moves the record from pending (bit 0) to
// loaded (bit 1) -- the inverse of bfmeClearESP (BfmeConv1977.cpp), which
// formats the same level name and clears bit 1. Layout follows the matched
// constructor as recorded in WindowManager_update.cpp; the +0x10 flags are
// written as a byte, so this view spells them unsigned char
// (m_flags, as the earlier bank named them).
#include <string.h>
#include "ascii_string.h"

#include "../../../Include/Common/ScalarTypes.h"



void bfmeApplyESP(const char *first, const char *second);

struct WindowManagerAptRecord
{
	AsciiString m_at00;
	UnsignedInt m_at04;
	UnsignedInt m_at08;
	UnsignedInt m_at0C;
	unsigned char m_flags;
	unsigned char m_tail[3];
};

class WindowManager
{
public:
	Bool bfmeRva00467F20(Int index);

private:
	unsigned char m_unreconstructed00[0xA8];
	WindowManagerAptRecord m_atA8[12];
};

Bool WindowManager::bfmeRva00467F20(Int index)
{
	if ((UnsignedInt)index >= 12)
		return false;
	WindowManagerAptRecord *record = &m_atA8[index];
	if (!(record->m_flags & 1))
		return false;
	if (record->m_flags & 2)
		return false;
	AsciiString path = record->m_at00;
	const char *dot = path.StringBase<char>::find('.');
	if (dot) {
		Int count = strlen(dot);
		while (count--)
			path.removeLastChar();
	}
	AsciiString level;
	level.format("/_level%d", index);
	bfmeApplyESP(path.str(), level.str());
	record->m_flags = (record->m_flags & ~1) | 2;
	return true;
}
