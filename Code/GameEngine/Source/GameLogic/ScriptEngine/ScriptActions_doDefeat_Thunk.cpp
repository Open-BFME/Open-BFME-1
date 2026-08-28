// cl: /DNDEBUG /MD /EHsc
// readable body of ?doDefeat@ScriptActions@@IAEXXZ: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();
private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
	unsigned char m_pad[0x118];
public:
	Bool m_existingState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void startEndGameTimer();
};
extern ScriptEngine *TheScriptEngine;

class GameLogic { public: void closeWindows(); };
extern GameLogic *TheGameLogic;

class VictoryConditions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual Bool amIObserver();
	virtual void slot17();
	virtual void showScreen(const AsciiString &eventName, Bool existingWindowState,
		const AsciiString &screen, const void *table);
};
extern VictoryConditions *TheVictoryConditions;

class BfmeDefeatScreenHolder
{
	unsigned char m_pad[4];
public:
	GameWindow *m_window;
};

class BfmeGameClient
{
	unsigned char m_pad[0x0c];
public:
	BfmeDefeatScreenHolder *m_defeatScreenHolder;
};
extern BfmeGameClient *TheGameClient;
extern unsigned char BfmeDefeatScreenTable[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
	unsigned char m_pad[0x1d];
public:
	Bool m_victorious;
};
extern CampaignManager *TheCampaignManager;

Bool __cdecl BfmeShouldShowGameOverEvent();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doDefeat();
	void doDisableInput();
private:
	unsigned char m_pad[4];
	GameWindow *m_messageWindow;
	Bool m_suppressNewWindows;
};

void ScriptActions::doDefeat()
{
	m_suppressNewWindows = false;
	TheGameLogic->closeWindows();
	doDisableInput();
	if (!m_suppressNewWindows)
	{
		BfmeDefeatScreenHolder *holder = TheGameClient->m_defeatScreenHolder;
		if (TheVictoryConditions && holder)
		{
			AsciiString screen("Gui_DefeatScreen");
			AsciiString eventName(BfmeShouldShowGameOverEvent()
				? "APT:EndGameOver" : "APT:EndDefeat");
			GameWindow *existingWindow = holder->m_window;
			TheVictoryConditions->showScreen(eventName,
				existingWindow ? existingWindow->m_existingState : false,
				screen, BfmeDefeatScreenTable);
		}
	}
	TheCampaignManager->m_victorious = false;
	TheScriptEngine->startEndGameTimer();
}
