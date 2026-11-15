// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x005383F0, 119 bytes. Cdecl helper in the Online Chat/CustomMatch
// dump: format APT:ConnectingPlayer%dName with index+1 and write the supplied
// UnicodeString through g_theWindowManager->bfme_setAptText.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class UnicodeString;

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. The local
// WindowManager view above is exactly the canonical pointee type, so the name
// only changes.
extern WindowManager *g_rva012F19E8WindowManager;

void setConnectingPlayerName( int index, const UnicodeString &text )
{
	AsciiString name;
	name.format( AsciiString( "APT:ConnectingPlayer%dName" ), index + 1 );
	g_rva012F19E8WindowManager->bfme_setAptText( name, text );
}
