// cl: /DNDEBUG /MD /EHsc

// ControlBar::resetContainData, retail 0x004A3B00, 59 bytes.
// Twin: ControlBarCommand.cpp. BFME also hides each command window after
// clearing the matching static ContainEntry. MAX_COMMANDS_PER_SET is 20.

enum { MAX_COMMANDS_PER_SET = 20 };

class GameWindow
{
public:
	int winHide(bool hide);
};

struct ContainEntry
{
	GameWindow *control;
	unsigned int objectID;
};

class ControlBar
{
protected:
	void resetContainData(void);

	char m_pad[0x100];
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];

	static ContainEntry m_containData[MAX_COMMANDS_PER_SET];
};

ContainEntry ControlBar::m_containData[MAX_COMMANDS_PER_SET];

void ControlBar::resetContainData(void)
{
	int i;

	for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		m_containData[i].control = 0;
		m_containData[i].objectID = 0;

		if (m_commandWindows[i])
			m_commandWindows[i]->winHide(true);
	}
}
