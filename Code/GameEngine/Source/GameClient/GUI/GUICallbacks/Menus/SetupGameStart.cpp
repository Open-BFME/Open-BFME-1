// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: setupGameStart, retail 0x004C6F70. The by-value map name is
// copied into GlobalData::m_pendingFile before the shell transition.

#include "ascii_string.h"

class SetupGameStartCampaignManagerView
{
public:
	void setGameDifficulty(int diff) { m_diff = diff; }

private:
	char m_pad[0x18];
	int m_diff;
};

class SetupGameStartGlobalDataView
{
public:
	char m_pad[0xb84];
	AsciiString m_pendingFile;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void reverseAnimatewindow();
};

class TransitionHandler
{
public:
	void setGroup(AsciiString name, int i);
};

extern SetupGameStartCampaignManagerView *TheCampaignManager;
extern SetupGameStartGlobalDataView *TheWritableGlobalData;
extern Shell *TheShell;
extern TransitionHandler *TheTransitionHandler;

void setupGameStart(AsciiString mapName, int diff)
{
	TheCampaignManager->setGameDifficulty(diff);
	AsciiString *pendingFile = &TheWritableGlobalData->m_pendingFile;
	pendingFile->set(mapName);
	TheShell->reverseAnimatewindow();
	TheTransitionHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
}
