// cl: /DNDEBUG /MD /EHsc
// ?initLANMultiPlayer@@YAXXZ
// ScoreScreen initLANMultiPlayer, retail 0x004E8A70, 206 bytes.
// GadgetTextEntrySetText takes UnicodeString by value; copy ctor and dtor are
// inline forwarders onto StringBase<unsigned short> so the EH saved-esp store
// lands before mov ecx,esp.

#define BFME_VSLOT(n) virtual void slot##n();

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &o ) : StringBase<unsigned short>( o ) {}
	~UnicodeString() {}
	static UnicodeString TheEmptyString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winHide( int hide );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43)
	virtual int winSetFocus( GameWindow *window );
};

class ChatHolder
{
public:
	char pad[0x5c];
	GameWindow *chat;
};

void grabMultiPlayerInfo( void );
void GadgetTextEntrySetText( GameWindow *textEntry, UnicodeString text );

extern GameWindowManager *TheWindowManager;
extern ChatHolder *s_chatHolder;

enum { SCORESCREEN_LAN = 2 };

static int screenType;
static GameWindow *staticTextGameSaved;
static GameWindow *textEntryChat;
static GameWindow *buttonEmote;
static GameWindow *chatBoxBorder;
static GameWindow *buttonContinue;
static GameWindow *buttonBuddies;
static GameWindow *listboxChatWindowScoreScreen;

void initLANMultiPlayer( void )
{
	screenType = SCORESCREEN_LAN;
	grabMultiPlayerInfo();
	GadgetTextEntrySetText( textEntryChat, UnicodeString::TheEmptyString );
	TheWindowManager->winSetFocus( textEntryChat );
	if ( staticTextGameSaved )
		staticTextGameSaved->winHide( 1 );
	if ( textEntryChat )
		textEntryChat->winHide( 0 );
	if ( buttonEmote )
		buttonEmote->winHide( 0 );
	if ( buttonContinue )
		buttonContinue->winHide( 1 );
	if ( listboxChatWindowScoreScreen )
		listboxChatWindowScoreScreen->winHide( 0 );
	if ( s_chatHolder )
		s_chatHolder->chat = listboxChatWindowScoreScreen;
	if ( chatBoxBorder )
		chatBoxBorder->winHide( 0 );
	if ( buttonBuddies )
		buttonBuddies->winHide( 1 );
}
