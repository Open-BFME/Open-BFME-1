// Retail 0x00538F00, 111 bytes.
// WOLBuddyOverlay.cpp supplies the callers. The retail vtable uses addText at
// +0xEC and a one-string method at +0xFC for the three color cases below.

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringData<T> *m_data;

	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	~UnicodeString() {}
};

enum GameSpyColors
{
	GSCOLOR_DEFAULT = 0,
	GSCOLOR_CURRENTROOM,
	GSCOLOR_ROOM,
	GSCOLOR_GAME,
	GSCOLOR_GAME_FULL,
	GSCOLOR_GAME_CRCMISMATCH,
	GSCOLOR_PLAYER_NORMAL,
	GSCOLOR_PLAYER_OWNER,
	GSCOLOR_PLAYER_BUDDY,
	GSCOLOR_PLAYER_SELF,
	GSCOLOR_PLAYER_IGNORED,
	GSCOLOR_CHAT_NORMAL,
	GSCOLOR_CHAT_EMOTE,
	GSCOLOR_CHAT_OWNER,
	GSCOLOR_CHAT_OWNER_EMOTE,
	GSCOLOR_CHAT_PRIVATE,
	GSCOLOR_CHAT_PRIVATE_EMOTE,
	GSCOLOR_CHAT_PRIVATE_OWNER,
	GSCOLOR_CHAT_PRIVATE_OWNER_EMOTE,
	GSCOLOR_CHAT_BUDDY,
	GSCOLOR_CHAT_SELF,
	GSCOLOR_ACCEPT_TRUE,
	GSCOLOR_ACCEPT_FALSE,
	GSCOLOR_MAP_SELECTED,
	GSCOLOR_MAP_UNSELECTED,
	GSCOLOR_MOTD,
	GSCOLOR_MOTD_HEADING,
	GSCOLOR_MAX
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
	virtual int addText( UnicodeString message, int color, GameWindow *window ) = 0;
	GAMESPY_SLOT( 60 ); GAMESPY_SLOT( 61 );
	virtual void sendChat( UnicodeString message, bool isEmote, GameWindow *window ) = 0;
	virtual int handleText( UnicodeString message ) = 0;
};
#undef GAMESPY_SLOT

extern GameSpyInfo *TheGameSpyInfo;
extern int GameSpyColor[];

void __stdcall GameSpyAddText( UnicodeString message, GameSpyColors color )
{
	if ( !TheGameSpyInfo )
		return;

	switch ( color )
	{
	case GSCOLOR_DEFAULT:
		// The cast preserves retail's by-value UnicodeString stack layout.
		TheGameSpyInfo->addText( **(UnicodeString **)&message, GameSpyColor[ GSCOLOR_DEFAULT ], 0 );
		break;
	case GSCOLOR_CURRENTROOM:
		TheGameSpyInfo->addText( **(UnicodeString **)&message, GameSpyColor[ 24 ], 0 );
		break;
	case GSCOLOR_ROOM:
		TheGameSpyInfo->handleText( **(UnicodeString **)&message );
		break;
	}
}
