// cl: /DNDEBUG /MD
//
// Retail 0x00516C10: open LanLobby.apt unless its singleton already exists.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
class BfmeAptScreenLanLobby;
extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;

// ?_bfme_showLanLobby@@YAXXZ
void _bfme_showLanLobby( void )
{
	if( reinterpret_cast<void * &>(g_rva012F4998LanLobby) == 0 )
		TheShell->push( AsciiString( "LanLobby.apt" ), false );
}
