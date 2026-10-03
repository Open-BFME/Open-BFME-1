// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?push@Shell@@QAEXVAsciiString@@_N@Z: game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp
// Open-BFME5: clean C++ reconstruction of the shell layout push path.

#include "ascii_string.h"

// The retail caller inlines StringBase's witnessed null/length test.
template <> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void runShutdown(bool *immediate);
	unsigned char m_pad[0x10];
	bool m_hidden;
};

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
void GameSpyCloseAllOverlays();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push(AsciiString filename, bool shutdownImmediate);
	void shutdownComplete(WindowLayout *layout, int unknown);
private:
	unsigned char m_unknown0[4];
	WindowLayout *m_screenStack[17];
	int m_screenCount;
	bool m_pendingPush;
	unsigned char m_gap[7];
	AsciiString m_pendingPushName;
};

void Shell::push(AsciiString filename, bool shutdownImmediate)
{
	if (filename.isEmpty())
		return;

	if (TheGameSpyInfo)
		GameSpyCloseAllOverlays();

	if (m_screenCount >= 16)
		return;

	AsciiString *pendingName = &m_pendingPushName;
	m_pendingPush = true;
	*pendingName = filename;

	WindowLayout *currentTop = m_screenCount ? m_screenStack[m_screenCount] : 0;
	if (currentTop && !currentTop->m_hidden)
		currentTop->runShutdown(&shutdownImmediate);
	else
		shutdownComplete(0, 0);
}
