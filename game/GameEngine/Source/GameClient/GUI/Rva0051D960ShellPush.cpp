// cl: /DNDEBUG /MD
//
// Leftovers on d_0050fec0.asm:
//   0x0051D960 35B  TheShell->push("Menus/MapSelectMenu.wnd", false)
//   0x0051D9D0 51B  if (TheGameState->doesSaveGameExist("00000000.sav")) this+0x264 = 1
// Same in-place StringBase<char> by-value slot as ShowLanLobby / ShowSkirmish.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;

class Rva0051D960Host
{
public:
	void pushMapSelect( int unused );
};

// ?pushMapSelect@Rva0051D960Host@@QAEXH@Z
void Rva0051D960Host::pushMapSelect( int )
{
	TheShell->push( AsciiString( "Menus/MapSelectMenu.wnd" ), false );
}

class GameState
{
public:
	bool doesSaveGameExist( AsciiString filename );
};

extern GameState *TheGameState;

class Rva0051D9D0Host
{
public:
	void checkDefaultSave( int unused );

private:
	char m_lead[0x264];
	int m_264;
};

// ?checkDefaultSave@Rva0051D9D0Host@@QAEXH@Z
void Rva0051D9D0Host::checkDefaultSave( int )
{
	if( TheGameState->doesSaveGameExist( AsciiString( "00000000.sav" ) ) )
		m_264 = 1;
}
