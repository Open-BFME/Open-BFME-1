// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
typedef bool Bool;

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
	unsigned char m_pad[0x118];
public:
	Bool m_existingState;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void startCloseWindowTimer();
	__declspec(noinline) void markMPLocalDefeatWindowShown();
private:
	unsigned char m_pad[0x17632];
	Bool m_mpLocalDefeatWindowShown;
};
extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void closeWindows();
};
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
// Retail global 0x012F079C is EA's TheVictoryConditions, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditions.cpp. The
// extern carries the canonical pointee type so the linked name is
// ?TheVictoryConditions@@3PAVVictoryConditionsInterface@@A; the TU-local
// VictoryConditions view above is reached through this cast helper.
class VictoryConditionsInterface;
extern VictoryConditionsInterface *TheVictoryConditions;
static inline VictoryConditions *localVictoryConditions()
{
	return (VictoryConditions *)TheVictoryConditions;
}

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
class GameClient;
extern GameClient *TheGameClient;
extern unsigned char BfmeDefeatScreenTable[];

__declspec(noinline) void ScriptEngine::markMPLocalDefeatWindowShown()
{
	m_mpLocalDefeatWindowShown = true;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
	unsigned char m_pad[0x1d];
public:
	Bool m_victorious;
};
extern CampaignManager *TheCampaignManager;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doLocalDefeat();
private:
	unsigned char m_pad[4];
	GameWindow *m_messageWindow;
	Bool m_suppressNewWindows;
};

void ScriptActions::doLocalDefeat()
{
	TheScriptEngine->markMPLocalDefeatWindowShown();
	m_suppressNewWindows = false;
	TheGameLogic->closeWindows();
	if (!m_suppressNewWindows && TheVictoryConditions && !localVictoryConditions()->amIObserver())
	{
		BfmeDefeatScreenHolder *holder = reinterpret_cast<BfmeGameClient *>(TheGameClient)->m_defeatScreenHolder;
		if (holder)
		{
			AsciiString screen("Gui_DefeatScreen");
			AsciiString eventName("APT:EndDefeat");
			GameWindow *existingWindow = holder->m_window;
			localVictoryConditions()->showScreen(eventName,
				existingWindow ? existingWindow->m_existingState : false,
				screen, BfmeDefeatScreenTable);
		}
	}
	TheCampaignManager->m_victorious = false;
	TheScriptEngine->startCloseWindowTimer();
}
