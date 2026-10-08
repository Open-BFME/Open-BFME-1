// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00538490, 119 bytes. Twin of setConnectingPlayerName: format
// APT:ConnectingPlayer%dStatus with index+1 and write the supplied
// UnicodeString through g_theWindowManager->bfme_setAptText.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	// Retail inlines the dtor: temporaries call releaseBuffer (0x00887940) directly.
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

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

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. The local
// WindowManager view above is exactly the canonical pointee type, so the name
// only changes.
extern WindowManager *g_rva012F19E8WindowManager;

void setConnectingPlayerStatus( int index, const UnicodeString &text )
{
	AsciiString name;
	name.format( AsciiString( "APT:ConnectingPlayer%dStatus" ), index + 1 );
	g_rva012F19E8WindowManager->bfme_setAptText( name, text );
}
