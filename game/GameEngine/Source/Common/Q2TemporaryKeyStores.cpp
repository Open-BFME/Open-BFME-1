// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// Seven 33-byte __thiscall members that build a string temporary from a
// stlport
// literal and hand it, by value, to one member of their own object:
//
//   push ecx                       ; reserve the by-value argument slot
//   push esi
//   push <FLAG> / push ecx         ; second argument, then the slot again
//   mov esi,ecx
//   mov [esp+0xc],esp              ; cleanup pointer for the in-place temporary
//   mov ecx,esp                    ; construct AT the argument slot
//   push <LITERAL> / call ?StringBase<char>::StringBase(char const *)
//   mov ecx,esi / call ?getInt@UserPreferences@@QBEHVAsciiString@@H@Z
//   pop esi / pop ecx / ret
//
// WHAT THE BYTES SHOW.  The temporary is never built somewhere else and
// copied: `mov ecx,esp` right after the argument slot is pushed constructs it
// IN PLACE at the outgoing argument, which is what MSVC does for a by-value
// class argument.  The callee pops both dwords (esp is back at the saved esi
// when `pop esi` runs), so it is __thiscall with two stack arguments, and the
// class is four bytes wide because one push reserves it.  Both calls take ecx
// from the object, so the store is a member of the same class this function
// belongs to.  `mov [esp+0xc],esp` records the temporary's address for
// cleanup.
//
// AsciiString is the real four-byte by-value type.  Its inline C-string
// constructor delegates directly to the matched StringBase<char> constructor
// at 0x00888BC0; the call at the end is UserPreferences::getInt, whose return
// value these setters discard.
//
// THE LITERALS ARE READ OUT OF RETAIL and re-checked by the build's
// string-reference gate: OverallWinStreak, OverallBestWinStreak,
// OverallLossStreak, OverallWorstLossStreak, PreferredSide, Highest1vs1Rank
// and Highest2vs2Rank.  All seven rows call the same getInt body, which is what
// makes them seven members of one class.
//
// TWO AXES: the literal and the second argument, which is 0 in six rows and 4
// in one.  21 of the 33 bytes are concrete.
//
// The second argument is int-width and could be an enumerator or a bool.  The
// address-derived owner calls the independently matched UserPreferences
// getInt member at 0x000A9490 through an explicit view of the same this pointer.
//
// The seven setter identities remain address-derived; the preference accessor
// and string type use their ledger-owned names.

#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/UserPreferences.h"

typedef AsciiString Q2AsciiString;

class Gen000A9490Owner
{
public:
	void Rva0009CEA0();
	void Rva0009CF00();
	void Rva0009CF60();
	void Rva0009CFC0();
	void Rva0009D020();
	void Rva000A9880();
	void Rva000A98E0();
};

#define Q2_TEMPORARY_KEY_STORE( NAME, LITERAL, FLAG )                     \
	void Gen000A9490Owner::NAME()                                         \
	{                                                                     \
		reinterpret_cast<UserPreferences *>(this)->getInt(                  \
			Q2AsciiString( LITERAL ), FLAG );                                 \
	}

Q2_TEMPORARY_KEY_STORE( Rva0009CEA0, "OverallWinStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009CF00, "OverallBestWinStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009CF60, "OverallLossStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009CFC0, "OverallWorstLossStreak", 0 )
Q2_TEMPORARY_KEY_STORE( Rva0009D020, "PreferredSide", 4 )
Q2_TEMPORARY_KEY_STORE( Rva000A9880, "Highest1vs1Rank", 0 )
Q2_TEMPORARY_KEY_STORE( Rva000A98E0, "Highest2vs2Rank", 0 )
