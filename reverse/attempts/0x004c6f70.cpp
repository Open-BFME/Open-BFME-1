// ?setupGameStart@@YAXVAsciiString@@H@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: setupGameStart, retail 0x004C6F70. Called from
// DifficultySelectSystem. No launchChallengeMenu branch: store difficulty at
// CampaignManager+0x18, copy the by-value map name into GlobalData::m_pendingFile
// at +0xb84, Shell::reverseAnimatewindow, then setGroup("FadeWholeScreen", 0).

#include "StringInline.h"

class CampaignManagerView
{
public:
	void setGameDifficulty(int diff) { m_diff = diff; }

private:
	char m_pad[0x18];
	int m_diff;
};

class PendingFile
{
public:
	void set(const AsciiString &s);
};

class GlobalDataView
{
public:
	char m_pad[0xb84];
	PendingFile m_pendingFile;
};

class ShellView
{
public:
	void reverseAnimatewindow();
};

class TransitionHandlerView
{
public:
	void setGroup(AsciiString name, int i);
};

extern CampaignManagerView *TheCampaignManager;
extern GlobalDataView *TheWritableGlobalData;
extern ShellView *TheShell;
extern TransitionHandlerView *TheTransitionHandler;

void setupGameStart(AsciiString mapName, int diff)
{
	TheCampaignManager->setGameDifficulty(diff);
	TheWritableGlobalData->m_pendingFile.set(mapName);
	TheShell->reverseAnimatewindow();
	TheTransitionHandler->setGroup(AsciiString("FadeWholeScreen"), 0);
}
