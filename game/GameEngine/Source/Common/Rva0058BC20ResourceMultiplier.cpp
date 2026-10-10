// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class CommandButton;
class GameWindow;

// Retail global 0x012F33F8 ?TheControlBar@@3PAVControlBar@@A.
// retail 0x58BC20 calls ILT 0x3B59D -> 0x4A0310 findCommandButton and
// ILT 0x3BCCD -> 0x4C1B60 rva004C1B60 (both matched ControlBar rows).
class ControlBar
{
public:
	const CommandButton *findCommandButton( const AsciiString &name );
	void rva004C1B60( GameWindow *window, void *command );
};
extern ControlBar *TheControlBar;

struct Rva0058BC20State
{
	float m_multiplier;
};

class Gen0058BC20
{
public:
	void handle( int unused );

private:
	Rva0058BC20State *m_state;
};

void Gen0058BC20::handle( int )
{
	if( m_state->m_multiplier != 1.0f )
	{
		const CommandButton *command;
		{
			AsciiString name( "NonCommand_ResourceMultiplier" );
			command = TheControlBar->findCommandButton( name );
		}
		if( command )
			TheControlBar->rva004C1B60( 0, (void *)command );
	}
}
