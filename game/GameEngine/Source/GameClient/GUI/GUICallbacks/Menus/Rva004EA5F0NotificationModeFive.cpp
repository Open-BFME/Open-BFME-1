// cl: /DNDEBUG /MD /EHsc
// Retail 0x004EA5F0 formats the buddy notification for non-five game modes.

template <typename T> struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_padding;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

	StringInlineData<T> *m_data;

	StringBase( const StringBase<T> &other );
	~StringBase();
	void set( const StringBase<T> &other );
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const AsciiString &other )
		: StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	bool isNotEmpty() const
	{
		return m_data && m_data->m_length != 0;
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void operator=( const UnicodeString &other )
	{
		StringBase<unsigned short>::set( other );
	}

	bool isNotEmpty() const
	{
		return m_data && m_data->m_length != 0;
	}

	void format( UnicodeString format, ... );
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

class BfmeAptChatFriendLogIn
{
public:
	void showFriendLogIn( const UnicodeString &text );
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

#define TheGameText004EA5F0 (*(GameTextInterface **)0x012F147C)
extern BfmeAptChatFriendLogIn *volatile g_d_012F4ACC;
extern unsigned int g_Va012F423C;
extern unsigned char g_Va012F4240;
extern int g_Va012F4244;
extern unsigned char g_Va012F4248;

void bfme_notificationModeFive( AsciiString nick, UnicodeString message )
{
	if ( g_d_012F4ACC )
	{
		if ( g_Va012F4240 && g_Va012F4244 > 1 )
			message = TheGameText004EA5F0->fetch( "Buddy:MultipleOnlineNotification" );

		if ( nick.isNotEmpty() )
			message.format( message, nick.str() );

		unsigned long now = timeGetTime();
		BfmeAptChatFriendLogIn *onlineShell = g_d_012F4ACC;
		UnicodeString *messagePtr = &message;
		g_Va012F423C = now + 3000;
		g_Va012F4248 = 1;
		onlineShell->showFriendLogIn( *messagePtr );
	}
}
