// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib

// FILE: GameWindowManagerScript_parseTooltip.cpp /////////////////////////////
//
// parseTooltip, retail 0x00485AB0. The .wnd keyword table names it: the triple
// in .data binds "TOOLTIP" to this address.
//
// Zero Hour's three lines, unchanged - BFME still has not translated the string.
//
// Kept out of GameWindowManagerScript.cpp so that file keeps serving its
// twenty-eight matched rows: retail's UnicodeString here is the StringBase
// -backed one, whose set() takes an explicit length and whose copy constructor
// builds the by-value temporary in retail's `mov [esp+N],esp' order, and
// swapping the string class under that TU would move every one of them.
//
// The length is computed by a call rather than folded: retail reaches the CRT
// through the import table even for a literal, so wcslen is spelled out where
// Zero Hour lets UnicodeString::set(const wchar_t *) do it.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <wchar.h>

#include "Common/UnicodeString.h"

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	void setTooltipText( UnicodeString tip );
};

// ?parseTooltip@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseTooltip( char *token, WinInstanceData *instData, char *buffer, void *data )
{
	UnicodeString tooltip;
	((StringBase<wchar_t> *)&tooltip)->set( L"Need tooltip translation",
										   (int)wcslen( L"Need tooltip translation" ) );

	/// @todo need to parse the tooltip in multibyte here

	instData->setTooltipText( tooltip );
	return true;
}
