// ?bfmeGetGroupTotalFrames@GameWindowTransitionsHandler@@QAEHVAsciiString@@@Z
// partial score=0.99 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int NameKeyType;

struct AsciiStringData
{
	int m_refCount;
	int m_length;
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	const char *str(void) const
	{
		return m_data ? m_data->m_text : "";
	}

private:
	AsciiStringData *m_data;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow;

class GameWindowManager
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot21(void) = 0;
	virtual void bfmeSlot22(void) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual void bfmeSlot26(void) = 0;
	virtual void bfmeSlot27(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual void bfmeSlot29(void) = 0;
	virtual void bfmeSlot30(void) = 0;
	virtual void bfmeSlot31(void) = 0;
	virtual void bfmeSlot32(void) = 0;
	virtual void bfmeSlot33(void) = 0;
	virtual void bfmeSlot34(void) = 0;
	virtual void bfmeSlot35(void) = 0;
	virtual void bfmeSlot36(void) = 0;
	virtual void bfmeSlot37(void) = 0;
	virtual void bfmeSlot38(void) = 0;
	virtual void bfmeSlot39(void) = 0;
	virtual void bfmeSlot40(void) = 0;
	virtual void bfmeSlot41(void) = 0;
	virtual void bfmeSlot42(void) = 0;
	virtual void bfmeSlot43(void) = 0;
	virtual void bfmeSlot44(void) = 0;
	virtual void bfmeSlot45(void) = 0;
	virtual void bfmeSlot46(void) = 0;
	virtual void bfmeSlot47(void) = 0;
	virtual void bfmeSlot48(void) = 0;
	virtual void bfmeSlot49(void) = 0;
	virtual void bfmeSlot50(void) = 0;
	virtual void bfmeSlot51(void) = 0;
	virtual void bfmeSlot52(void) = 0;
	virtual void bfmeSlot53(void) = 0;
	virtual void bfmeSlot54(void) = 0;
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id) = 0;
};

extern GameWindowManager *TheWindowManager;

class Transition
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void init(GameWindow *window) = 0;
};

class TransitionWindow
{
public:
	void init(void);

private:
	AsciiString m_winName;
	int m_frameDelay;
	NameKeyType m_winID;
	GameWindow *m_win;
	Transition *m_transition;
	int m_currentFrameDelay;
};

inline void TransitionWindow::init(void)
{
	m_winID = TheNameKeyGenerator->nameToKey(m_winName.str());
	m_win = TheWindowManager->winGetWindowFromId(0, m_winID);
	m_currentFrameDelay = m_frameDelay;
	m_transition->init(m_win);
}

class TransitionGroup;

class GameWindowTransitionsHandler
{
public:
	int bfmeGetGroupTotalFrames(AsciiString groupName);

	unsigned char m_unmodelled[0x50];
	int m_transitionEndFrame;

private:
	TransitionGroup *findGroup(AsciiString groupName);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class TransitionGroup
{
public:
	void init(void);
	int getTotalFrames(void);

private:
	bool m_fireOnce;
	unsigned char m_unmodelled01[3];
	_STL::list<TransitionWindow *> m_transitionWindowList;
	int m_directionMultiplier;
	int m_currentFrame;
	AsciiString m_name;
};

// BFME extends the ZH initialization with an end-frame cache on the global
// transition handler.
// ?init@TransitionGroup@@QAEXXZ
void TransitionGroup::init(void)
{
	m_currentFrame = 0;
	m_directionMultiplier = 1;
	_STL::list<TransitionWindow *>::iterator it = m_transitionWindowList.begin();
	while (it != m_transitionWindowList.end())
	{
		TransitionWindow *window = *it;
		window->init();
		++it;
	}

	TheTransitionHandler->m_transitionEndFrame = getTotalFrames() + 3;
}

// Return the duration of a named transition group, or zero when absent.
// ?bfmeGetGroupTotalFrames@GameWindowTransitionsHandler@@QAEHVAsciiString@@@Z
int GameWindowTransitionsHandler::bfmeGetGroupTotalFrames(AsciiString groupName)
{
	int totalFrames = 0;
	TransitionGroup *group = findGroup(groupName);
	if (group)
		totalFrames = group->getTotalFrames();
	return totalFrames;
}
