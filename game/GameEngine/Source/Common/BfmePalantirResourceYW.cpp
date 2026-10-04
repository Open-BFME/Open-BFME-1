// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the palantir resource update at retail 0x00565620, 197 bytes.
// A function-local static holds the property key; the value is formatted from
// the argument, or set to a single space when the argument is negative.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// The string operations use StringBase<char>'s matched constructor, set and
// releaseBuffer bodies. Retail's call through ILT 0x00030CFB reaches the
// AsciiString overload in WindowManager_setAptText.cpp at 0x0046CC30.
// No game/ header declares WindowManager.
class WindowManager
{
};

extern void j_00030cfb();

typedef void (WindowManager::*SetAptTextCall)(const AsciiString &key, const AsciiString &value);

union SetAptTextCast
{
	void (*raw)();
	SetAptTextCall member;
};

// Defined once in game/GameEngine/Source/GameClient/GUI/WindowManager.cpp.
extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

// ?bfmeSetPalantirYW@@YAXH@Z
void bfmeSetPalantirYW(int count)
{
	static AsciiString s_bfmeKeyYW("APT:PalantirResources");

	AsciiString value;

	if (count >= 0)
		value.format(AsciiString("%d"), count);
	else
		value.StringBase<char>::set(" ", 1);

	SetAptTextCast cast;
	cast.raw = j_00030cfb;
	(g_rva012F19E8WindowManager->*cast.member)(s_bfmeKeyYW, value);
}
