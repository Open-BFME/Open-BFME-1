// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x005383F0, 119 bytes. Cdecl helper in the Online Chat/CustomMatch
// dump: format APT:ConnectingPlayer%dName with index+1 and write the supplied
// UnicodeString through g_theWindowManager->bfme_setAptText.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void __cdecl format( AsciiString fmt, ... );
};

class UnicodeString;

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

void setConnectingPlayerName( int index, const UnicodeString &text )
{
	AsciiString name;
	name.format( AsciiString( "APT:ConnectingPlayer%dName" ), index + 1 );
	g_theWindowManager->bfme_setAptText( name, text );
}
