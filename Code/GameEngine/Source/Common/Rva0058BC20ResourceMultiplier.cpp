// cl: /DNDEBUG /MD /EHsc

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
extern float g_rva0058BC20DefaultMultiplier;

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
	if( m_state->m_multiplier != g_rva0058BC20DefaultMultiplier )
	{
		void *command;
		{
			AsciiString name( "NonCommand_ResourceMultiplier" );
			command = g_rva0058C100CommandManager->find( &name );
		}
		if( command )
			g_rva0058C100CommandManager->execute( 0, command );
	}
}
