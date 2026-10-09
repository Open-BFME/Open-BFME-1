// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class Rva0058C100CommandManager
{
public:
	void *find( const AsciiString *name );
	void execute( int value, void *command );
};

// Retail global 0x012F33F8; the canonical mangled spelling is
// ?TheControlBar@@3PAVControlBar@@A, so the pointee must be the real
// ControlBar and only the calls need the TU-local view of it.
class ControlBar;
extern ControlBar *TheControlBar;

class CommandButton;
class GameWindow;

// Retail ILT 0x0003B59D -> 0x004A0310 is the matched
// ControlBar::findCommandButton row and ILT 0x0003BCCD -> 0x004C1B60 the
// matched ControlBar::rva004C1B60 row.
class ControlBar
{
public:
	const CommandButton *findCommandButton( const AsciiString &name );
	void rva004C1B60( GameWindow *window, void *data );
};

struct Rva0058BCD0State
{
	int m_index;
};

class Gen0058BCD0
{
public:
	void handle( int unused );

private:
	Rva0058BCD0State *m_state;
};

void Gen0058BCD0::handle( int )
{
	if( m_state->m_index >= 0 )
	{
		void *command;
		{
			AsciiString name( "NonCommand_Resources" );
			command = (void *)TheControlBar->findCommandButton( name );
		}
		if( command )
			TheControlBar->rva004C1B60( (GameWindow *)0, command );
	}
}
