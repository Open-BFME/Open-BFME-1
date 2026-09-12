// cl: /DNDEBUG /MD /EHsc

#include "../../../../../../../reference/shims/stringinline/StringInline.h"

typedef bool Bool;

#define TRUE true
#define FALSE false

extern "C" unsigned __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

namespace _STL
{
template <class T> class char_traits;
template <class T> class allocator;

template <class C, class Traits, class Allocator> class basic_string
{
public:
	basic_string &assign(const C *first, const C *last);
	basic_string &operator=(const C *text)
	{
		return assign(text, text + strlen(text));
	}

	C *begin;
	C *end;
	C *capacity;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name)
	{
		return nameToKey(name.str());
	}
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow
{
public:
	int winHide(bool hide);
	int winEnable(bool enable);
};

class WindowLayout
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void hide(bool immediate) = 0;
	virtual void bringForward() = 0;
};

class GameWindowManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual int winSetFocus(GameWindow *window) = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id) = 0;
};

class Shell
{
public:
	WindowLayout *getPopupReplayLayout();
};

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD = 0,
	RECORDERMODETYPE_PLAYBACK = 1,
	RECORDERMODETYPE_NONE = 2
};

class RecorderClass
{
public:
	AsciiString getLastReplayFileName();
	RecorderModeType getMode();
	bool isMultiplayer();
};

class LANAPI
{
private:
	char m_padding[0x5c];

public:
	GameWindow *chatWindow;
};

class GameLogic
{
private:
	char m_padding[0x10c];

public:
	int m_gameMode;
};

class TransitionHandler
{
public:
	void setGroup(AsciiString groupName, int immediate = 0);
};

extern GameWindowManager *TheWindowManager;
extern Shell *TheShell;
extern RecorderClass *TheRecorder;
extern LANAPI *TheLAN;
extern GameLogic *TheGameLogic;
extern TransitionHandler *TheTransitionHandler;

extern _STL::string LastReplayFileName;
extern Bool g_playMusic;
extern Bool ReplayWasPressed;

static NameKeyType parentID;
static NameKeyType buttonOkID;
static NameKeyType textEntryChatID;
static NameKeyType buttonEmoteID;
static NameKeyType chatBoxBorderID;
static NameKeyType buttonBuddiesID;
static NameKeyType buttonContinueID;
static NameKeyType buttonSaveReplayID;
static NameKeyType listboxChatWindowScoreScreenID;

static GameWindow *parent;
static GameWindow *buttonOk;
static GameWindow *buttonContinue;
static GameWindow *textEntryChat;
static GameWindow *buttonEmote;
static GameWindow *chatBoxBorder;
static GameWindow *buttonBuddies;
static GameWindow *staticTextGameSaved;
static GameWindow *listboxChatWindowScoreScreen;

static Bool overidePlayerDisplayName;
static Bool canSaveReplay;
static Bool s_needToFinishSinglePlayerInit;
static WindowLayout *s_blankLayout;
static Bool buttonIsFinishCampaign;

void initSinglePlayer(void);
void initSkirmish(void);
void initLANMultiPlayer(void);
void initInternetMultiPlayer(void);
void initReplayMultiPlayer(void);
void initReplaySinglePlayer(void);

class Rva004E8DC0ScoreScreen
{
public:
	static void init(WindowLayout *layout, void *userData);
};

// ?ScoreScreenInit@@YAXPAVWindowLayout@@PAX@Z
void Rva004E8DC0ScoreScreen::init(WindowLayout *layout, void *)
{
	g_playMusic = TRUE;
	buttonIsFinishCampaign = FALSE;

	parentID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ParentScoreScreen"));
	buttonOkID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ButtonOk"));
	textEntryChatID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:TextEntryChat"));
	buttonEmoteID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ButtonEmote"));
	listboxChatWindowScoreScreenID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ListboxChatWindowScoreScreen"));
	chatBoxBorderID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ChatBoxBorder"));
	buttonBuddiesID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ButtonBuddy"));
	buttonContinueID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ButtonContinue"));
	buttonSaveReplayID = TheNameKeyGenerator->nameToKey(
		AsciiString("ScoreScreen.wnd:ButtonSaveReplay"));

	parent = TheWindowManager->winGetWindowFromId(0, parentID);
	buttonOk = TheWindowManager->winGetWindowFromId(parent, buttonOkID);
	textEntryChat = TheWindowManager->winGetWindowFromId(
		parent, textEntryChatID);
	buttonEmote = TheWindowManager->winGetWindowFromId(parent, buttonEmoteID);
	listboxChatWindowScoreScreen = TheWindowManager->winGetWindowFromId(
		parent, listboxChatWindowScoreScreenID);
	if (TheLAN != 0)
		TheLAN->chatWindow = listboxChatWindowScoreScreen;
	chatBoxBorder = TheWindowManager->winGetWindowFromId(
		parent, chatBoxBorderID);
	buttonContinue = TheWindowManager->winGetWindowFromId(
		parent, buttonContinueID);
	buttonBuddies = TheWindowManager->winGetWindowFromId(
		parent, buttonBuddiesID);
	staticTextGameSaved = TheWindowManager->winGetWindowFromId(
		parent, TheNameKeyGenerator->nameToKey(
			"ScoreScreen.wnd:StaticTextGameSaveComplete"));

	LastReplayFileName = TheRecorder->getLastReplayFileName().str();
	staticTextGameSaved->winHide(TRUE);
	overidePlayerDisplayName = FALSE;
	WindowLayout *replayLayout = TheShell->getPopupReplayLayout();
	if (replayLayout != 0)
		replayLayout->hide(TRUE);
	canSaveReplay = FALSE;
	if (TheRecorder->getMode() == RECORDERMODETYPE_RECORD)
		canSaveReplay = TRUE;
	GameWindow *buttonSaveReplay = TheWindowManager->winGetWindowFromId(
		parent, buttonSaveReplayID);
	if (TheRecorder->getMode() == RECORDERMODETYPE_NONE && buttonSaveReplay)
		buttonSaveReplay->winEnable(FALSE);

	s_needToFinishSinglePlayerInit = FALSE;
	if (TheGameLogic->m_gameMode == 3)
	{
		if (buttonSaveReplay)
			buttonSaveReplay->winHide(TRUE);

		if (TheRecorder->isMultiplayer())
		{
			initReplayMultiPlayer();
			TheTransitionHandler->setGroup("ScoreScreenShow");
		}
		else
		{
			overidePlayerDisplayName = TRUE;
			initReplaySinglePlayer();
			TheTransitionHandler->setGroup("ScoreScreenShow");
		}
	}
	else if (TheGameLogic->m_gameMode == 5)
	{
		initInternetMultiPlayer();
		TheTransitionHandler->setGroup("ScoreScreenShow");
	}
	else if (TheGameLogic->m_gameMode == 1)
	{
		initLANMultiPlayer();
		TheTransitionHandler->setGroup("ScoreScreenShow");
	}
	else if (TheGameLogic->m_gameMode == 2)
	{
		initSkirmish();
		TheTransitionHandler->setGroup("ScoreScreenShow");
	}
	else
	{
		overidePlayerDisplayName = TRUE;
		initSinglePlayer();
	}

	layout->hide(FALSE);
	TheWindowManager->winSetFocus(parent);
	ReplayWasPressed = FALSE;
	if (s_blankLayout != 0)
	{
		s_blankLayout->hide(FALSE);
		s_blankLayout->bringForward();
	}
}
