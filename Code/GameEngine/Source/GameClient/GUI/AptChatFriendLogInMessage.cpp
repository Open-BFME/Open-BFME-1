// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0055C480: set APT:ChatFriendLogInMessage then invoke ChatMessageOpen
// on the movie at this+0x250.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	void *m_data;
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4 );
};

extern WindowManager *g_theWindowManager;

class BfmeAptChatFriendLogIn
{
public:
	void showFriendLogIn( const UnicodeString &text );

private:
	unsigned char m_unmodelled[ 0x250 ];
	int m_movie;
};

// ?showFriendLogIn@BfmeAptChatFriendLogIn@@QAEXABVUnicodeString@@@Z
void BfmeAptChatFriendLogIn::showFriendLogIn( const UnicodeString &text )
{
	{
		AsciiString name( "APT:ChatFriendLogInMessage" );
		g_theWindowManager->bfme_setAptText( name, text );
	}
	g_theWindowManager->unidentified_00015235(
		m_movie, "ChatMessageOpen", 0, 0, 0, 0, 0, 0 );
}
