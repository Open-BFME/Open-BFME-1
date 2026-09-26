// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

// This is the ZH GameWindowTransitionsHandler::parseWindow callback.  The
// retail field table at 0x010F97D0 contains the WinName/Transition/FrameDelay
// fields and is registered for the WindowTransition block.  The BFME table is
// retained as the existing data symbol; this TU only supplies the ABI view
// needed by the callback body.
typedef unsigned int NameKeyType;

class INI
{
public:
	void initFromINI( void *object, const void *fieldTable );
};

#include "ascii_string.h"

class TransitionWindow
{
public:
	TransitionWindow()
	{
		m_currentFrameDelay = m_frameDelay = 0;
		m_winID = 0;
		m_win = 0;
		m_transition = 0;
	}

private:
	AsciiString m_winName;
	int m_frameDelay;
	NameKeyType m_winID;
	void *m_win;
	void *m_transition;
	int m_currentFrameDelay;
};

class TransitionGroup
{
public:
	void addWindow( TransitionWindow *window )
	{
		if (!window)
			return;
		m_transitionWindowList.push_back( window );
	}

private:
	bool m_fireOnce;
	unsigned char m_padding[3];
	_STL::list<TransitionWindow *> m_transitionWindowList;
};

extern const unsigned char Rva0048BD60FieldTable[];

class GameWindowTransitionsHandler
{
public:
	static void parseWindow( INI *ini, void *instance, void *store,
		const void *userData );
};

// ?parseWindow@GameWindowTransitionsHandler@@SAXPAVINI@@PAX1PBX@Z
void GameWindowTransitionsHandler::parseWindow( INI *ini, void *instance,
	void *store, const void *userData )
{
	TransitionWindow *transWin = new TransitionWindow;
	ini->initFromINI( transWin, Rva0048BD60FieldTable );
	((TransitionGroup *)instance)->addWindow( transWin );
}
