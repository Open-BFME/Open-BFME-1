// cl: /O2 /Ob0
//
// Retail 0x003839E0. GameLogic path QuitMenu takes when TheNetwork is null
// (Network::quitGame is the other arm). Always posts MSG_CLEAR_GAME_DATA.
// LAN/Internet may also post MSG_SELF_DESTRUCT(true) if GameInfo vslot+0x30
// is false. Non-multiplayer plus pause restores mouse/input and two audio
// vslot+0x30 calls. InGameUI+0x12BE is set unconditionally. Tail-calls the
// helper on 0x012F7048. Descriptive name: local-game quit, not a ZH twin.

typedef bool Bool;

enum
{
	GAME_LAN = 1,
	GAME_SKIRMISH = 2,
	GAME_INTERNET = 5,
	MSG_CLEAR_GAME_DATA = 0x1D,
	MSG_SELF_DESTRUCT = 0x447
};

class GameMessage
{
public:
	void appendBooleanArgument(Bool arg);
};

class MessageStream
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual GameMessage *appendMessage(unsigned int type) = 0;
};

class GameInfo
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual Bool slot30(void) = 0;
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(Bool visible);
};

class InGameUI
{
public:
	void _bfme_setEngineInputEnabled(Bool enabled);
	char m_pad[0x12BE];
	unsigned char m_flag12BE;
};

class AudioManager
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void audioOp(int affect, int a, int b) = 0;
};

class BfmeOneAQA
{
public:
	void bfmeStopAQA(void);
};

extern GameInfo *TheGameInfo;
extern MessageStream *TheMessageStream;
extern Mouse *TheMouse;
extern InGameUI *TheInGameUI;
#define TheAudio (*(AudioManager **)0x012ED668)
extern "C" BfmeOneAQA *g_bfmeStateDF;

class GameLogic
{
public:
	void _bfme_quitLocalGame(void);

	char m_pad[0x10C];
	int m_gameMode;
	char m_pad110[0x0C];
	Bool m_gamePaused;
	unsigned char m_pad11D;
	Bool m_inputEnabledMemory;
	Bool m_mouseVisibleMemory;
};

void GameLogic::_bfme_quitLocalGame(void)
{
	int mode = m_gameMode;
	if (mode == GAME_LAN || mode == GAME_INTERNET)
	{
		if (mode != GAME_SKIRMISH)
		{
			if (TheGameInfo && !TheGameInfo->slot30())
			{
				GameMessage *msg = TheMessageStream->appendMessage(MSG_SELF_DESTRUCT);
				msg->appendBooleanArgument(true);
			}
		}
	}
	TheMessageStream->appendMessage(MSG_CLEAR_GAME_DATA);

	mode = m_gameMode;
	if (mode != GAME_LAN && mode != GAME_INTERNET)
	{
		if (m_gamePaused)
		{
			Bool vis = m_mouseVisibleMemory;
			m_gamePaused = false;
			TheMouse->_bfme_setEngineVisibility(vis);
			if (m_inputEnabledMemory)
				TheInGameUI->_bfme_setEngineInputEnabled(true);
			TheAudio->audioOp(0x3F, 3, 0);
			TheAudio->audioOp(0x3F, 4, 1);
		}
	}
	TheInGameUI->m_flag12BE = 1;

	if (g_bfmeStateDF)
		g_bfmeStateDF->bfmeStopAQA();
}
