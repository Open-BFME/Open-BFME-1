// cl: /DNDEBUG /MD
//
// Retail 0x00516C10: open LanLobby.apt unless its singleton already exists.

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
extern void *g_obj12F4998;

// ?_bfme_showLanLobby@@YAXXZ
void _bfme_showLanLobby( void )
{
	if( g_obj12F4998 == 0 )
		TheShell->push( AsciiString( "LanLobby.apt" ), false );
}
