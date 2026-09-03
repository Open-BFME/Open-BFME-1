// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

private:
	char *m_data;
};

class Rva0058C100CommandManager
{
public:
	void *find( const AsciiString *name );
	void execute( int value, void *command );
};

extern Rva0058C100CommandManager *g_rva0058C100CommandManager;

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
			command = g_rva0058C100CommandManager->find( &name );
		}
		if( command )
			g_rva0058C100CommandManager->execute( 0, command );
	}
}
