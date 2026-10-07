// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the label commit at retail 0x004D1080, 117 bytes.  The label
// arrives by value and is released at the end; the receiver for set is an
// embedded member of the global base, which is why its address is materialised
// with an add rather than folded into a displacement.

// The label is a StringBase<char> (BFME's AsciiString), and both the copy into
// the slot and the release at the end are real StringBase bodies the tree
// already owns: ?set@?$StringBase@D@@QAEXABV1@@Z at 0x00887C90 and
// ?releaseBuffer@?$StringBase@D@@AAEXXZ at 0x00887940. ascii_string.h is the
// real header for that class, and its comments record both bodies.
//
// The by-value parameter is a real AsciiString; the function's identity is
// ?bfmeCommitYH@@YAXVAsciiString@@@Z (MapSelectMenu.cpp spelling); the layout is StringBase<char>'s, which
// the real AsciiString inherits unchanged.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail's by-value parameter is a StringBase<char> (BFME's AsciiString), and
// its copy is released at the end by the header's inline
// { validate(); releaseBuffer(); }, i.e. a direct call to
// ?releaseBuffer@?$StringBase@D@@AAEXXZ (0x00887940), the body the tree already
// owns.  Retail holds no separate body for ??1AsciiStringYH@@QAE@XZ: that
// release is the inherited one, inlined into this function's single scope exit,
// exactly as ascii_string.h spells AsciiString's own destructor (a bare `{}`
// over StringBase<char>'s inline destructor).  So the parameter type inherits
// AsciiString and declares nothing; giving it a member of its own instead makes
// VC7.1 emit a COMDAT copy of a destructor name retail does not have, and that
// copy claims a retail address.
class AsciiStringYH : public AsciiString
{
};

class BfmeBaseYH
{
public:
	char m_bfmePad000[0xB84];				// +0x000
	AsciiStringYH m_bfmeLabel;				// +0xB84
};

// Both notifications go out through retail's own incremental-link thunks,
// which the ledger owns as ?j_<rva>@@YAXXZ; retail carries no body name for
// either callee. VC7.1 has no __thiscall function-pointer type, so each is
// taken as a pointer-to-member out of a union, the pattern the tree's other
// matched bodies already use.
class Rva004D1080Receiver {};

extern void j_0003dcee();
extern void j_0000bd7f();

typedef void (Rva004D1080Receiver::*Rva0003DCEE)();
typedef void (Rva004D1080Receiver::*Rva0000BD7F)(int);

template<class T> __forceinline T Rva004D1080Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALLYH(T, obj, fn) (((Rva004D1080Receiver*)(obj))->*Rva004D1080Member<T>(fn))

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// bfmeRefreshYH() through it, so the pointee stays the local BfmeOtherYH view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

// Canonical identity of the retail global at 0x012ED5C8, defined once by
// game/GameEngine/Source/Common/GlobalData.cpp as
// ?TheWritableGlobalData@@3PAVGlobalData@@A.  The member address keeps the local
// view and casts at the use.
class GlobalData;
extern GlobalData *TheWritableGlobalData;		// retail 0x012ED5C8
// Retail global 0x012F4B58; EA's own name for this pointer is
// `Shell *TheShell`, defined once in
// game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp.  BfmeThingYH above
// is this TU's view of the pointee, so the call casts at the use.
class Shell;

extern Shell *TheShell;						// retail 0x012F4B58
// Map selection commit flag at retail VA 0x012F3E6D.
bool g_bfmeDirtyYH = false;					// retail 0x012F3E6D

// ?bfmeCommitYH@@YAXVAsciiString@@@Z (the spelling MapSelectMenu.cpp calls)
void __cdecl bfmeCommitYH(AsciiString label)
{
	g_bfmeDirtyYH = true;

	AsciiStringYH *slot = &((BfmeBaseYH *)TheWritableGlobalData)->m_bfmeLabel;

	StringBase<char> *src = (StringBase<char> *)&label;

	((StringBase<char> *)slot)->set(*src);

	CALLYH(Rva0003DCEE, TheShell, j_0003dcee)();

	if (g_rva012F19E8WindowManager != 0)
		CALLYH(Rva0000BD7F, g_rva012F19E8WindowManager, j_0000bd7f)(0);
}
