// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Zero Hour's CommandSet::parseCommandButton (retail 0x0049C7C0
// 207 B) as a standalone TU.  The token names a command button looked up
// through TheControlBar (VA 0x012F33F8) with a temporary AsciiString; an
// unknown name throws INIException(3 "Unknown command '%s' found in command
// set. File: %s Line: %d\n") -- BFME's INI::getFilename returns the name BY
// VALUE (hidden-pointer call into a stack temporary whose inline str() is
// read) and getLineNum is the 16-byte accessor at 0x00850810.  The button is
// stored at the userData index of the store array.

typedef int Int;

extern const char g_bfmeEmptyAscii[];

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }

	const char *str( void ) const { return m_data ? ((const char *)m_data) + 8 : g_bfmeEmptyAscii; }

private:
	void releaseBuffer( void );
	void *m_data;
};

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	AsciiString getFilename( void ) const;
	Int getLineNum( void ) const;
};

class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton( const AsciiString &name );
};

extern ControlBar *TheControlBar;

class CommandSet
{
public:
	static void parseCommandButton( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseCommandButton@CommandSet@@SAXPAVINI@@PAX1PBX@Z
void CommandSet::parseCommandButton( INI *ini, void *, void *store, const void *userData )
{
	const char *token = ini->getNextToken();
	const CommandButton *commandButton;
	{
		AsciiString name( token );
		commandButton = TheControlBar->findCommandButton( name );
	}
	if( commandButton == 0 )
	{
		throw INIException( 3, "Unknown command '%s' found in command set. File: %s Line: %d\n",
			token, ini->getFilename().str(), ini->getLineNum() );
	}
	const CommandButton **buttonArray = (const CommandButton **)store;
	buttonArray[ (Int)userData ] = commandButton;
}
