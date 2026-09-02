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

void __stdcall rva0058C100ObserveNext( void * )
{
	void *command;
	{
		AsciiString name( "NonCommand_ObserveNextPlayer" );
		command = g_rva0058C100CommandManager->find( &name );
	}
	if( command )
		g_rva0058C100CommandManager->execute( 0, command );
}

void __stdcall rva0058C1A0ObservePrior( void * )
{
	void *command;
	{
		AsciiString name( "NonCommand_ObservePriorPlayer" );
		command = g_rva0058C100CommandManager->find( &name );
	}
	if( command )
		g_rva0058C100CommandManager->execute( 0, command );
}
