// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x006BAB60.  This is the Win32GameEngine update loop from the
// upstream Win32 game-engine source, with the BFME singleton and vtable
// layouts made explicit at the one method that is being recovered.

#include <windows.h>

#define BFME_VSLOT(n) virtual void slot##n() = 0;

class GameEngine
{
public:
	BFME_VSLOT(0)
	BFME_VSLOT(1)
	BFME_VSLOT(2)
	BFME_VSLOT(3)
	BFME_VSLOT(4)
	BFME_VSLOT(5)
	BFME_VSLOT(6)
	BFME_VSLOT(7)
	BFME_VSLOT(8)
	BFME_VSLOT(9)
	BFME_VSLOT(10)
	BFME_VSLOT(11)
	BFME_VSLOT(12)
	BFME_VSLOT(13)
	virtual bool getQuitting() = 0;
};

class Win32GameEngine
{
public:
	BFME_VSLOT(0)
	BFME_VSLOT(1)
	BFME_VSLOT(2)
	BFME_VSLOT(3)
	BFME_VSLOT(4)
	BFME_VSLOT(5)
	BFME_VSLOT(6)
	BFME_VSLOT(7)
	BFME_VSLOT(8)
	BFME_VSLOT(9)
	BFME_VSLOT(10)
	BFME_VSLOT(11)
	BFME_VSLOT(12)
	BFME_VSLOT(13)
	BFME_VSLOT(14)
	BFME_VSLOT(15)
	virtual void serviceWindowsOS() = 0;
	virtual bool isActive() = 0;
	virtual void update();
};

class LANAPI
{
public:
	BFME_VSLOT(0)
	BFME_VSLOT(1)
	BFME_VSLOT(2)
	BFME_VSLOT(3)
	BFME_VSLOT(4)
	virtual void update() = 0;
	BFME_VSLOT(6)
	BFME_VSLOT(7)
	BFME_VSLOT(8)
	virtual void setIsActive(bool isActive) = 0;
};

#undef BFME_VSLOT

struct Rva00367E30Logic
{
	char m_unmodelled00[0x10c];
	int m_gameMode;
};

extern void j_000021df(void);
extern GameEngine *TheGameEngine;
extern LANAPI *TheLAN;
extern Rva00367E30Logic *TheBfmeGameLogic;
extern void *Rva0048CD50WindowHandle;
extern DWORD TheMessageTime;

void Win32GameEngine::update(void)
{
	j_000021df();

	if (Rva0048CD50WindowHandle && ::IsIconic(Rva0048CD50WindowHandle))
	{
		while (Rva0048CD50WindowHandle && ::IsIconic(Rva0048CD50WindowHandle))
		{
			::Sleep(5);
			serviceWindowsOS();

			if (TheLAN != NULL)
			{
				TheLAN->setIsActive(isActive());
				TheLAN->update();
			}

			if (TheGameEngine->getQuitting() ||
				TheBfmeGameLogic->m_gameMode == 5 ||
				TheBfmeGameLogic->m_gameMode == 1)
			{
				break;
			}
		}
	}

	serviceWindowsOS();
}

void Win32GameEngine::serviceWindowsOS(void)
{
	MSG msg;
	int returnValue;

	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		returnValue = GetMessage(&msg, NULL, 0, 0);
		TheMessageTime = msg.time;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		TheMessageTime = 0;
	}
}
