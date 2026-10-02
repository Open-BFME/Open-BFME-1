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
			command = ((Rva0058C100CommandManager *)TheControlBar)->find( &name );
		}
		if( command )
			((Rva0058C100CommandManager *)TheControlBar)->execute( 0, command );
	}
}
