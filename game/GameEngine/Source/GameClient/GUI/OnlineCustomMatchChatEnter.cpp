// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch::chatEnter, retail 0x0053A5D0, 254 bytes.
// The constructor at 0x00545310 registers this body under the retail selector
// string "AptOnline::CustomMatch::ChatEnter", which is where the name comes
// from. The body reads the chat entry gadget at this+0x194, clears the gadget,
// trims the text, and sends anything left to GameSpyInfo::sendChat unless
// handleSlashCommands at 0x00539E60 already consumed it.

template <typename T> struct StringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[ 1 ];
};

class UnicodeString;

template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	void set( const StringBase<T> &src );
	void trim();

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringHeader<T> *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	UnicodeString &operator=( const UnicodeString &other )
	{
		set( other );
		return *this;
	}

	void trim() { StringBase<unsigned short>::trim(); }
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }

	static UnicodeString TheEmptyString;
};

class GameWindow;

UnicodeString GadgetTextEntryGetText( GameWindow *window );
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

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
	GAMESPY_SLOT( 56 ); GAMESPY_SLOT( 57 ); GAMESPY_SLOT( 58 ); GAMESPY_SLOT( 59 );
	GAMESPY_SLOT( 60 ); GAMESPY_SLOT( 61 );
	virtual void sendChat( UnicodeString message, bool isEmote, GameWindow *window ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;

class BfmeAptScreenOnlineCustomMatch
{
public:
	void chatEnter( const char *name );
	bool handleSlashCommands( UnicodeString uText );

private:
	unsigned char m_head[ 0x194 ];
	GameWindow *m_chatEntry;
};

void BfmeAptScreenOnlineCustomMatch::chatEnter( const char *name )
{
	(void)name;
	if( m_chatEntry == 0 )
		return;

	UnicodeString text;
	text = GadgetTextEntryGetText( m_chatEntry );
	GadgetTextEntrySetText( m_chatEntry, UnicodeString::TheEmptyString );
	text.trim();
	if( !text.isEmpty() )
	{
		if( !handleSlashCommands( text ) )
			TheGameSpyInfo->sendChat( text, false, 0 );
	}
}
