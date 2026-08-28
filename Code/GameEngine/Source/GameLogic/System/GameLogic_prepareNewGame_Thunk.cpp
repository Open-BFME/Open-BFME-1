// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?prepareNewGame@GameLogic@@QAEXHW4GameDifficulty@@H@Z: Code/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL
};

enum GameMode
{
	GAME_SHELL = 4
};

class AsciiString;

template <class T>
class StringBase
{
private:
	friend class AsciiString;

	StringBase(const char *text);
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other);
	void clear();

	Bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	UnsignedInt winClearStatus(UnsignedInt status);
};

// BFME made the WindowLayout operations virtual; the Zero Hour header did not.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void runInit(void *userData);
	virtual ~WindowLayout();
	virtual void runUpdate(void *userData);
	virtual void runShutdown(void *userData);
	virtual void hide(Bool immediate);
	virtual void bringForward();

	GameWindow *getFirstWindow() const
	{
		return m_firstWindow;
	}

private:
	AsciiString m_filename;
	GameWindow *m_firstWindow;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual WindowLayout *winCreateLayout(AsciiString filename);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void setObjectsShouldReceiveDifficultyBonus(Bool receive);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void hide(Bool immediate);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_000[0x08];
	AsciiString m_mapName;
	unsigned char m_unreconstructed_00C[0xB78];
	AsciiString m_pendingFile;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void prepareNewGame(Int gameMode, GameDifficulty diff, Int rankPoints);

	unsigned char m_unreconstructed_000[0x8C];
	Int m_rankPointsToAddAtGameStart;
	unsigned char m_unreconstructed_090[0x0C];
	GameDifficulty m_gameDifficulty;
	Bool m_startNewGame;
	unsigned char m_unreconstructed_0A1[0x03];
	WindowLayout *m_background;
	unsigned char m_unreconstructed_0A8[0x64];
	Int m_gameMode;
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;
extern GameWindowManager *TheWindowManager;
extern GlobalData *TheWritableGlobalData;
extern Shell *TheShell;

void GameLogic::prepareNewGame(Int gameMode, GameDifficulty diff, Int rankPoints)
{
	TheScriptEngine->setObjectsShouldReceiveDifficultyBonus(true);
	TheGameLogic->m_gameDifficulty = diff;

	if (!m_background)
	{
		m_background = TheWindowManager->winCreateLayout("Menus/BlankWindow.wnd");
		m_background->hide(false);
		m_background->bringForward();
	}

	m_background->getFirstWindow()->winClearStatus(0x80);
	TheGameLogic->m_gameMode = gameMode;

	if (!TheWritableGlobalData->m_pendingFile.isEmpty())
	{
		TheWritableGlobalData->m_mapName = TheWritableGlobalData->m_pendingFile;
		TheWritableGlobalData->m_pendingFile.clear();
	}

	m_rankPointsToAddAtGameStart = rankPoints;
	if (TheGameLogic->m_gameMode != GAME_SHELL)
		TheShell->hide(true);

	m_startNewGame = false;
}
