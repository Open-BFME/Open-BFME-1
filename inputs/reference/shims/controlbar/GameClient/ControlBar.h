// TU-scoped BFME ControlBar layout shim.
//
// The ZH reference ControlBar.h (which BFME's ControlBar.cpp TU still uses,
// unshimmed) mismatches retail's true field offsets: BFME dropped/changed a
// swath of ZH-only fields (purchase-science UI, upgrade cameo rows, etc.)
// that don't exist in this LOTR-era build. Full reconstruction of that
// interior layout has not been done yet. Only the boundaries proven so far
// (each from a retail accessor body's disassembly) are represented, via
// padding blobs between them:
//
//   m_specialPowerShortcutButtons[10] @ this+0xCC (retail RVA 0x4A07D0,
//     ControlBar::showSpecialPowerShortcut: `lea ebx,[esi+0xCC]` array base,
//     4-byte stride confirmed by the loop's `add ebx,4`; element count from
//     the proven 0xCC..0xF4 gap (0x28 bytes / 4 = 10) — not independently
//     confirmed, just the only size consistent with both boundaries)
//   m_currentlyUsedSpecialPowersButtons @ this+0xF4 (same body:
//     `mov eax,[esi+0xF4]` loop bound)
//   m_specialPowerShortcutParent @ this+0xFC (retail RVA 0x49D4A0,
//     ControlBar::hideSpecialPowerShortcut: `mov ecx,[ecx+0xFC]`; also read
//     at +0xFC in showSpecialPowerShortcut)
//   m_commandButtons @ this+0x28 and m_commandSets @ this+0x2c -- both at
//     ZH's own offsets, NO drift. Retail has two 126-byte find-by-name loops:
//     0x4A01B0 reads [ecx+0x28] and walks its nodes via node+0x14, 0x4A0270
//     reads [ecx+0x2c] and walks via node+0x60. ZH declares CommandButton's
//     m_name/m_command/m_next at +0xc/+0x10/+0x14 and CommandSet's
//     m_name/m_command[N]/m_next at +0xc/+0x10/+0x10+4N, so node+0x14 is a
//     CommandButton and node+0x60 is a CommandSet with N=20 (BFME raised
//     MAX_COMMANDS_PER_SET from ZH's 18). Hence 0x4A01B0 is
//     findNonConstCommandButton and 0x4A0270 is findNonConstCommandSet.
//     Independently: retail's findCommandSet (0x4A0340, pinned by the byte-true
//     call site in ScriptActions_doNamedUseCommandButtonAbility_Thunk.cpp
//     through ILT 0x48CCA) calls 0x4A0270, and findCommandButton (0x4A0310)
//     calls 0x4A01B0.
//
// showSpecialPowerShortcut itself does NOT verify yet with this layout: its
// body also calls TheScriptEngine->isGameEnding() (retail reads the field at
// TheScriptEngine+0x17080; the current ScriptEngine reference header puts it
// at +0x10AA4 — ScriptEngine has its own BFME layout drift, out of this
// track) and Player::hasAnyShortcutSpecialPower() (retail's caller does a
// 32-bit `test eax,eax` on the result; the reference Player.h declares it
// returning `Bool`/bool, which compiles to an 8-bit `test al,al` here — the
// real BFME declaration is evidently a wider return type). Both are
// out-of-track class drifts; only land showSpecialPowerShortcut once they
// are separately fixed. Retail's body also omits the ZH source's
// `&& !hasAnyShortcutSelection()` clause entirely — don't port that back in.
//
// History, so the next reader does not re-derive it: 540ea686f wrote this
// header with ONE list class, called it CommandButton, and moved its m_next
// from ZH's +0x14 to +0x60 plus ControlBar's list head from +0x28 to +0x2c to
// make 0x4A0270 fit -- then documented those two moves as "BFME's interior
// grew by 0x4C bytes of LOTR-only fields". Both moves were artifacts of a
// swapped identity: 0x4A0270 is the CommandSet loop, and under the correct
// names every offset here is ZH's. 1f298d015 then landed that body in the
// ledger as findNonConstCommandButton. The row is retracted; do not re-add it
// at 0x4A0270.
//
// This header intentionally declares nothing else — it exists only for the
// small set of ControlBar member functions ported into ControlBarFields.cpp
// that touch fields at or before this proven boundary. Do NOT #include this
// from ControlBar.cpp itself: that TU has 40+ already-matched functions
// compiled against the (also wrong, but load-bearing) ZH header layout for
// fields before this boundary, and swapping headers there would need the
// full interior reconstructed first.

#pragma once

#ifndef __CONTROLBAR_H_
#define __CONTROLBAR_H_

#include "Common/SubsystemInterface.h"
#include "Common/AsciiString.h"

class GameWindow;

// StringBase<char>::Header layout mirrored here (see
// Code/Libraries/Source/WWVegas/WWLib/string_base.h) so findNonConstCommandSet
// can reproduce retail's inlined length-prefixed compare: the retail body (RVA
// 0x4A0270) reads a CommandSet's name header directly ([ecx+0xc], length at
// +0x4, char data at +0x8) and never calls AsciiString::compare()/operator==
// (both real out-of-line functions elsewhere in this codebase, matched from
// __declspec(naked) bodies in string_base.cpp) -- there is no CALL instruction
// in the whole 126B body for the comparison itself. AsciiString's only member
// (ascii_string.h's m_text) is that same Header* despite the name.
struct BFMEStringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

// Overridable : MemoryPoolObject is vtable + m_nextOverride + m_isOverride =
// 0xc bytes with this codebase's 4-byte Bool, so both list classes put m_name
// at +0xc, exactly where ZH's declaration order already puts it. Neither class
// drifts from ZH; only CommandSet's inline command array is longer here.
class CommandButton
{

public:

	const AsciiString &getName( void ) const { return m_name; }
	CommandButton *friend_getNext( void ) { return m_next; }
	const CommandButton *getNext( void ) const { return m_next; }

private:

	unsigned char m_unreconstructed_00[0xc];					///< vtable + Overridable (unchanged from ZH)

	AsciiString m_name;										///< retail this+0xc

	unsigned char m_unreconstructed_10[0x14 - 0xc - sizeof(AsciiString)];	///< ZH's GUICommandType m_command

	CommandButton *m_next;										///< retail this+0x14 (ZH offset; 0x4A01B0 walks via node+0x14)

};

// ZH's CommandSet is m_name, then `const CommandButton *m_command[
// MAX_COMMANDS_PER_SET ]`, then m_next. Retail 0x4A0270 walks via node+0x60,
// which fixes the array at 20 entries -- BFME raised ZH's 18. The array itself
// is never read by any body ported here; it exists to place m_next.
class CommandSet
{

public:

	const AsciiString &getName( void ) const { return m_name; }
	CommandSet *friend_getNext( void ) { return m_next; }
	const CommandSet *getNext( void ) const { return m_next; }

private:

	unsigned char m_unreconstructed_00[0xc];					///< vtable + Overridable (unchanged from ZH)

	AsciiString m_name;										///< retail this+0xc

	const CommandButton *m_command[20];						///< retail this+0x10, MAX_COMMANDS_PER_SET (ZH has 18)

	CommandSet *m_next;										///< retail this+0x60

};

//-------------------------------------------------------------------------------------------------
class ControlBar : public SubsystemInterface
{

public:

	ControlBar( void );
	virtual ~ControlBar( void );

	void hideSpecialPowerShortcut( void );

protected:

	CommandButton *findNonConstCommandButton( const AsciiString &name );	///< IAE-mangled (protected) to match ZH's access level

private:

	CommandSet *findNonConstCommandSet( const AsciiString &name );	///< AAE-mangled (private) to match ZH's access level

	// Unreconstructed interior: SubsystemInterface's vtable ptr + AsciiString
	// m_name (8 bytes total, sizeof(SubsystemInterface)) plus not-yet-pinned
	// ControlBar fields, padded so the next proven field lands at its real
	// offset. Do not read individual bytes out of this blob.
	unsigned char m_unreconstructed_08[0x28 - sizeof(SubsystemInterface)];

	CommandButton *m_commandButtons;							///< retail this+0x28 (ZH offset; 0x4A01B0: `mov ebp,[ecx+0x28]`)

	CommandSet *m_commandSets;								///< retail this+0x2c (ZH offset; 0x4A0270: `mov eax,[ecx+0x2c]`)

	unsigned char m_unreconstructed_30[0xCC - 0x2c - 4];

	GameWindow *m_specialPowerShortcutButtons[10];			///< retail this+0xCC (ZH header has this+0x1A0, MAX_SPECIAL_POWER_SHORTCUTS=11 there); array fills the whole 0xCC..0xF4 gap, no padding needed

	int m_currentlyUsedSpecialPowersButtons;				///< retail this+0xF4

	unsigned char m_unreconstructed_F8[0xFC - 0xF4 - sizeof(int)];	///< ZH has m_specialPowerLayout (WindowLayout*) here; not touched by any function ported so far

	GameWindow *m_specialPowerShortcutParent;			///< retail this+0xFC (ZH header has this+0x184)

};

#endif // __CONTROLBAR_H_
