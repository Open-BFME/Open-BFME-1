// cl: /DNDEBUG /MD
//
// Retail 0x0055C180: open OnlineShell.apt unless its singleton already exists.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
class BfmeAptScreenOnlineShell;
extern BfmeAptScreenOnlineShell *g_obj12F4ACC;

// ?_bfme_showOnlineShell@@YAXXZ
void _bfme_showOnlineShell( void )
{
	if( reinterpret_cast<void * &>(g_obj12F4ACC) == 0 )
		TheShell->push( AsciiString( "OnlineShell.apt" ), false );
}
