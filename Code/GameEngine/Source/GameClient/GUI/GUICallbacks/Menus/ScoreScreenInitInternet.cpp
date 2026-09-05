// cl: /DNDEBUG /MD /EHsc
// ?initInternetMultiPlayer@@YAXXZ
// ScoreScreen initInternetMultiPlayer, retail 0x004E8B80, 309 bytes.
// ZH source: GeneralsMD ScoreScreen.cpp:1034. BFME dropped the two academy
// windows (like initReplaySinglePlayer/initReplayMultiPlayer already landed)
// and added the same [global]+0x5c chat-window store initLANMultiPlayer uses
// (ScoreScreenInitLAN.cpp). GadgetTextEntrySetText takes UnicodeString by
// value; copy ctor/dtor are inline forwarders onto StringBase<unsigned short>
// so the EH saved-esp store lands before mov ecx,esp.
// buttonBuddies visibility reads TheGameSpyInfo->getLocalProfileID() through
// a view class: BFME inserted seven vtable slots before that ZH method
// (UserPreferences.cpp uses the same BfmeGameSpyInfoLocalProfileView shape).
// The trailing BuddyRequest matches BUDDYREQUEST_SETSTATUS/GP_ONLINE with
// statusString "Online" and an empty locationString.

#include <string.h>

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

// BFME chat-holder struct: initLANMultiPlayer stores the same listbox pointer
// into [global]+0x5c through this shape (ScoreScreenInitLAN.cpp).
class ChatHolder
{
public:
	char pad[0x5c];
	GameWindow *chat;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyInfo;

// BFME added seven vtable slots before ZH's getLocalProfileID, moving it from
// slot 28 (+0x70) here to +0x54 in the plain ZH interface; see
// Common/UserPreferences.cpp for the identical shape and comment.
class BfmeGameSpyInfoLocalProfileView
{
public:
	virtual void unused00() = 0, unused01() = 0, unused02() = 0, unused03() = 0;
	virtual void unused04() = 0, unused05() = 0, unused06() = 0, unused07() = 0;
	virtual void unused08() = 0, unused09() = 0, unused10() = 0, unused11() = 0;
	virtual void unused12() = 0, unused13() = 0, unused14() = 0, unused15() = 0;
	virtual void unused16() = 0, unused17() = 0, unused18() = 0, unused19() = 0;
	virtual void unused20() = 0, unused21() = 0, unused22() = 0, unused23() = 0;
	virtual void unused24() = 0, unused25() = 0, unused26() = 0, unused27() = 0;
	virtual int getLocalProfileID() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
// (matched exactly here: no BFME vtable shift on this interface.)
struct BuddyRequest
{
	enum { BUDDYREQUEST_SETSTATUS = 9 };
	int buddyRequestType;
	union
	{
		struct
		{
			int status;
			char statusString[256];
			char locationString[256];
		} status;
		char _pad[0x2B8 - 4];
	} arg;
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface() {}
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void addRequest( const BuddyRequest &req );
};

void grabMultiPlayerInfo( void );
void GadgetTextEntrySetText( GameWindow *textEntry, UnicodeString text );

extern GameWindowManager *TheWindowManager;
extern ChatHolder *s_chatHolder;
extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

enum { GP_ONLINE = 1 };
enum { SCORESCREEN_INTERNET = 3 };

static int screenType;
static GameWindow *staticTextGameSaved;
static GameWindow *textEntryChat;
static GameWindow *buttonEmote;
static GameWindow *chatBoxBorder;
static GameWindow *buttonContinue;
static GameWindow *buttonBuddies;
static GameWindow *listboxChatWindowScoreScreen;

// ?initInternetMultiPlayer@@YAXXZ
void initInternetMultiPlayer( void )
{
	screenType = SCORESCREEN_INTERNET;
	grabMultiPlayerInfo();
	GadgetTextEntrySetText( textEntryChat, UnicodeString::TheEmptyString );
	TheWindowManager->winSetFocus( textEntryChat );
	if ( staticTextGameSaved )
		staticTextGameSaved->winHide( 1 );
	if ( buttonContinue )
		buttonContinue->winHide( 1 );
	if ( textEntryChat )
		textEntryChat->winHide( 1 );
	if ( buttonEmote )
		buttonEmote->winHide( 1 );
	if ( listboxChatWindowScoreScreen )
		listboxChatWindowScoreScreen->winHide( 0 );
	if ( s_chatHolder )
		s_chatHolder->chat = listboxChatWindowScoreScreen;
	if ( chatBoxBorder )
		chatBoxBorder->winHide( 0 );

	if ( TheGameSpyInfo && reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>( TheGameSpyInfo )->getLocalProfileID() == 0 )
		buttonBuddies->winHide( 1 );
	else
		buttonBuddies->winHide( 0 );

	if ( !TheGameSpyBuddyMessageQueue )
		return;

	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_SETSTATUS;
	req.arg.status.status = GP_ONLINE;
	strcpy( req.arg.status.statusString, "Online" );
	strcpy( req.arg.status.locationString, "" );
	TheGameSpyBuddyMessageQueue->addRequest( req );
}
