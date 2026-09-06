// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Near-twin of ?handleSlashCommands@BfmeAptScreenOnlineCustomMatch@@QAE_NVUnicodeString@@@Z
// (0x00539E60, OnlineCustomMatchHandleSlashCommands.cpp): byte-identical body,
// the only proven difference is calling convention -- retail ends in a bare
// `ret` (no stack cleanup) instead of the member function's `ret 4`, so this
// is a free (cdecl) function taking the same by-value UnicodeString hidden
// pointer argument rather than a thiscall member. That two-byte saving
// (twice, once per return path) is also what turns one `jne` from the near
// form to the short form a few bytes earlier -- no other instruction differs.
// Address-derived name: real symbol unidentified.

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[ 1 ];
};

class UnicodeString;
class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void translate( const UnicodeString &src );
	char getCharAt( int index ) const
	{
		return m_data ? m_data->m_text[ index ] : 0;
	}
	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
	bool nextToken( AsciiString *tok, const char *seps );
	void toLower();
	int compare( const char *other ) const;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}
	const unsigned short *str() const
	{
		static const unsigned short empty[ 1 ] = { 0 };
		return m_data ? m_data->m_text : empty;
	}
	void format( UnicodeString fmt, ... );
};

class GameWindow;

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 ); GAMESPY_SLOT( 51 );
	GAMESPY_SLOT( 52 ); GAMESPY_SLOT( 53 ); GAMESPY_SLOT( 54 ); GAMESPY_SLOT( 55 );
	GAMESPY_SLOT( 56 ); GAMESPY_SLOT( 57 ); GAMESPY_SLOT( 58 );
	virtual void addText( UnicodeString message, int color, GameWindow *window ) = 0;
	GAMESPY_SLOT( 60 ); GAMESPY_SLOT( 61 );
	virtual void sendChat( UnicodeString message, bool isEmote, GameWindow *window ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;
extern int GameSpyColor[];
extern int isThreadHosting;

enum { GSCOLOR_DEFAULT = 0 };

// ?Rva004F1FF0HandleSlashCommands@@YA_NVUnicodeString@@@Z
bool Rva004F1FF0HandleSlashCommands( UnicodeString uText )
{
	AsciiString message;
	message.translate( uText );
	if( message.getCharAt( 0 ) != '/' )
		return false;

	AsciiString remainder( message.str() + 1 );
	AsciiString token;
	remainder.nextToken( &token, 0 );
	token.toLower();

	if( token.compare( "host" ) == 0 )
	{
		UnicodeString s;
		s.format( UnicodeString( L"Hosting qr2:%d thread:%d" ), 0, isThreadHosting );
		TheGameSpyInfo->addText( s, GameSpyColor[ GSCOLOR_DEFAULT ], 0 );
		return true;
	}
	else if( token.compare( "me" ) == 0 && uText.getLength() > 4 )
	{
		TheGameSpyInfo->sendChat( UnicodeString( uText.str() + 4 ), true, 0 );
		return true;
	}

	return false;
}
