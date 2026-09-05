// cl: /DNDEBUG /MD
// IMEManager::openCandidateList. ZH twin with BFME offsets and inlined
// updateProperties (GetKeyboardLayout + ImmGetProperty).

extern "C" {
	__declspec(dllimport) void *__stdcall GetKeyboardLayout(unsigned int thread);
	unsigned int __stdcall ImmGetProperty(void *hkl, unsigned int index);
}

class GameFont
{
public:
	int m_pad;
	int height;
};

class GameWindow
{
public:
	void winHide(bool hide);
	int winBringToTop(void);
	int winGetScreenPosition(int *x, int *y);
	int winGetSize(int *w, int *h);
	int winGetCursorPosition(int *x, int *y);
	GameFont *winGetFont(void);
	int winSetPosition(int x, int y);
	char m_pad[0x1F4 - 0x00];
	int m_flag1F4;
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58();
	virtual int winSetModal(GameWindow *window);
};

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual int getWidth(void);
};

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;

class IMEManager
{
public:
	void updateCandidateList(int candidateFlags);
	void resizeCandidateWindow(int pageSize);
	void openCandidateList(int candidateFlags);

private:
	char m_pad00[0x0C];
	GameWindow *m_window;
	char m_pad10[0x302C - 0x10];
	int m_indexBase;
	char m_pad3030[0x3034 - 0x3030];
	int m_pageSize;
	char m_pad3038[0x3044 - 0x3038];
	bool m_unicodeIME;
	char m_pad3045[0x304C - 0x3045];
	GameWindow *m_candidateWindow;
};

void IMEManager::openCandidateList(int candidateFlags)
{
	if (m_candidateWindow == 0)
		return;

	updateCandidateList(candidateFlags);
	resizeCandidateWindow(m_pageSize);

	m_candidateWindow->winHide(false);
	m_candidateWindow->winBringToTop();
	m_candidateWindow->m_flag1F4 = 0;
	TheWindowManager->winSetModal(m_candidateWindow);

	int wx, wy, wwidth, wheight, wcursorx, wcursory;
	int cx, cy, cwidth, cheight;

	if (m_window)
	{
		m_window->winGetScreenPosition(&wx, &wy);
		m_window->winGetSize(&wwidth, &wheight);
		m_window->winGetCursorPosition(&wcursorx, &wcursory);
		m_window->winGetFont();
	}
	else
	{
		wx = wy = 0;
		wwidth = 10;
		wheight = 10;
		wcursorx = 0;
		wcursory = 0;
	}

	m_candidateWindow->winGetSize(&cwidth, &cheight);
	cx = TheDisplay->getWidth() - cwidth;
	cy = 0;

	void *kb = GetKeyboardLayout(0);
	unsigned int prop = ImmGetProperty(kb, 4);
	m_indexBase = (prop >> 0x12) & 1;
	m_unicodeIME = ((prop >> 0x13) & 1) != 0;

	m_candidateWindow->winSetPosition(cx, cy);
}
