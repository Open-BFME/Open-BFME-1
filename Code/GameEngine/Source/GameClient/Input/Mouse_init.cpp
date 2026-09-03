// cl: /O2 /Ob0

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);
#pragma intrinsic(memset)

__declspec(dllimport) unsigned long __stdcall timeGetTime();

class UnicodeString
{
public:
	void clear();
	void *m_data;
};

class GlobalData
{
public:
	char m_pad[0xA95];
	unsigned char m_winCursors;
};

extern GlobalData *TheWritableGlobalData;

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;

class Mouse
{
public:
	virtual void init();

private:
	char m_pad0[0x10E0 - 4];
	int m_currentRedrawMode;
	char m_pad1[0x10F8 - 0x10E4];
	unsigned char m_numButtons;
	unsigned char m_numAxes;
	unsigned char m_forceFeedback;
	char m_pad2[0x1100 - 0x10FB];
	UnicodeString m_tooltipString;
	UnicodeString m_cursorText;
	char m_pad3[0x110C - 0x1108];
	unsigned char m_displayTooltip;
	char m_pad4[0x1110 - 0x110D];
	unsigned char m_mouseEvents[0x3C00];
	unsigned char m_currMouse[0x3C];
	unsigned char m_prevMouse[0x3C];
	int m_minX;
	int m_maxX;
	int m_minY;
	int m_maxY;
	int m_inputFrame;
	int m_deadInputFrame;
	unsigned char m_inputMovesAbsolute;
	char m_pad5[0x4DA8 - 0x4DA1];
	int m_currentCursor;
	void *m_cursorTextDisplayString;
	char m_pad6[0x4DDC - 0x4DB0];
	unsigned long m_stillTime;
	char m_pad7[0x4E00 - 0x4DE0];
	int m_eventsThisFrame;
};

void Mouse::init()
{
	if (TheWritableGlobalData && TheWritableGlobalData->m_winCursors)
		m_currentRedrawMode = 0;

	m_numButtons = 2;
	m_numAxes = 2;
	m_forceFeedback = 0;
	m_displayTooltip = 0;
	m_tooltipString.clear();
	m_cursorText.clear();
	m_stillTime = timeGetTime();

	memset(m_mouseEvents, 0, sizeof(m_mouseEvents));
	memset(m_currMouse, 0, sizeof(m_currMouse));
	memset(m_prevMouse, 0, sizeof(m_prevMouse));

	m_minX = 0;
	m_maxX = 799;
	m_minY = 0;
	m_maxY = 599;
	m_inputFrame = 0;
	m_deadInputFrame = 0;
	m_inputMovesAbsolute = 0;
	m_eventsThisFrame = 0;
	m_currentCursor = 2;
	m_cursorTextDisplayString = TheDisplayStringManager->newDisplayString();
}
