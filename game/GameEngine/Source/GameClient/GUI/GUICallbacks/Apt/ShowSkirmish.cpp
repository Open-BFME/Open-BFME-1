// cl: /DNDEBUG /MD
//
// Retail 0x00579440: open Skirmish.apt unless its singleton already exists.

#include "../../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
class BfmeAptScreenSkirmish;
extern BfmeAptScreenSkirmish *Rva012F4B54Skirmish;

// ?_bfme_showSkirmish@@YAXXZ
void _bfme_showSkirmish( void )
{
	if( reinterpret_cast<void * &>(Rva012F4B54Skirmish) == 0 )
		TheShell->push( AsciiString( "Skirmish.apt" ), false );
}
