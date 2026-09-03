// cl: /DNDEBUG /MD
//
// Retail 0x004E89C0 / 0x004E8D10: ScoreScreen.cpp's two replay inits.  Both
// store SCORESCREEN_REPLAY, grab the matching player-info helper, then
// winHide(TRUE) the same seven chat/continue/buddy windows (BFME dropped the
// two academy windows ZH still hides).  The bodies differ only in the grab
// callee and the hide order.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winHide(int hide);
};

void grabSinglePlayerInfo(void);
void grabMultiPlayerInfo(void);

enum { SCORESCREEN_REPLAY = 4 };

static int screenType;
static GameWindow *staticTextGameSaved;
static GameWindow *textEntryChat;
static GameWindow *buttonEmote;
static GameWindow *chatBoxBorder;
static GameWindow *buttonContinue;
static GameWindow *buttonBuddies;
static GameWindow *listboxChatWindowScoreScreen;

// ?initReplaySinglePlayer@@YAXXZ
void initReplaySinglePlayer(void)
{
	screenType = SCORESCREEN_REPLAY;
	grabSinglePlayerInfo();
	if (staticTextGameSaved)
		staticTextGameSaved->winHide(1);
	if (textEntryChat)
		textEntryChat->winHide(1);
	if (buttonEmote)
		buttonEmote->winHide(1);
	if (chatBoxBorder)
		chatBoxBorder->winHide(1);
	if (buttonContinue)
		buttonContinue->winHide(1);
	if (buttonBuddies)
		buttonBuddies->winHide(1);
	if (listboxChatWindowScoreScreen)
		listboxChatWindowScoreScreen->winHide(1);
}

// ?initReplayMultiPlayer@@YAXXZ
void initReplayMultiPlayer(void)
{
	screenType = SCORESCREEN_REPLAY;
	grabMultiPlayerInfo();
	if (staticTextGameSaved)
		staticTextGameSaved->winHide(1);
	if (textEntryChat)
		textEntryChat->winHide(1);
	if (buttonEmote)
		buttonEmote->winHide(1);
	if (listboxChatWindowScoreScreen)
		listboxChatWindowScoreScreen->winHide(1);
	if (chatBoxBorder)
		chatBoxBorder->winHide(1);
	if (buttonContinue)
		buttonContinue->winHide(1);
	if (buttonBuddies)
		buttonBuddies->winHide(1);
}
