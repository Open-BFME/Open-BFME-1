// ?deleteLoadScreen@GameLogic@@QAEXXZ
// partial score=0.55 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
//
// GameLogic method at retail 0x0038D100 (1516 B including its 8-entry mode
// jump table).  It came in as an __emit lift named deleteLoadScreen, but it
// returns a Bool (al=1 on every exit) and itself calls the real Zero Hour
// deleteLoadScreen shape at 0x00382CE0 (delete m_loadScreen, clear it) and
// the updateLoadProgress shape at 0x00382CC0.  Its real name is not
// recovered, so it keeps the address.  Callers: GameEngine's client
// subsystem update and 0x004329D0, both through ILT 0x00028E4B's family.
//
// What it does: while the +0x94 flag is set it pumps the load screen for the
// first frames of a network game, then clears the flag and fades the load
// screen out through TheTransitionHandler's FadeWholeScreen group, choosing
// the fade by game mode, and finally restores the mouse and audio.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

class GameEngine
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual void vslot24(void);
	virtual void vslot28(void);
	virtual void vslot2C(void);
	virtual void vslot30(void);
	virtual void vslot34(void);
	virtual void vslot38(void);
	virtual void vslot3C(void);
	virtual void vslot40(void);                                           // OS/message pump
};

class NetworkInterface
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual void vslot24(void);
	virtual void vslot28(void);
	virtual void vslot2C(void);
	virtual void vslot30(void);
	virtual void vslot34(void);
	virtual void vslot38(void);
	virtual void vslot3C(void);
	virtual void vslot40(void);
	virtual void vslot44(void);
	virtual void vslot48(void);
	virtual void vslot4C(void);
	virtual void vslot50(void);
	virtual void vslot54(void);
	virtual void vslot58(void);
	virtual void vslot5C(void);
	virtual void vslot60(void);
	virtual void vslot64(void);
	virtual void vslot68(void);
	virtual void vslot6C(void);
	virtual void vslot70(void);
	virtual void vslot74(void);
	virtual void vslot78(void);
	virtual void vslot7C(void);
	virtual void vslot80(void);
	virtual void vslot84(void);
	virtual void vslot88(void);
	virtual void vslot8C(void);
	virtual void vslot90(void);
	virtual void vslot94(void);
	virtual void vslot98(void);
	virtual void vslot9C(void);
	virtual void vslotA0(void);
	virtual void vslotA4(void);
	virtual void vslotA8(void);
	virtual void vslotAC(void);
	virtual Bool _bfme_isWaitingForPlayers(void);                        // +0xB0
};

class Display
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual void vslot24(void);
	virtual void vslot28(void);
	virtual void vslot2C(void);
	virtual void vslot30(void);
	virtual void vslot34(void);
	virtual void vslot38(void);
	virtual void vslot3C(void);
	virtual void vslot40(void);
	virtual void vslot44(void);
	virtual void vslot48(void);
	virtual void vslot4C(void);
	virtual void vslot50(void);
	virtual void vslot54(void);
	virtual void vslot58(void);
	virtual void vslot5C(void);
	virtual void vslot60(void);
	virtual void vslot64(void);
	virtual void vslot68(void);
	virtual void vslot6C(void);
	virtual void vslot70(void);
	virtual void vslot74(void);
	virtual void vslot78(void);
	virtual void vslot7C(void);
	virtual void vslot80(void);
	virtual void vslot84(void);
	virtual void vslot88(void);
	virtual void vslot8C(void);
	virtual void vslot90(void);
	virtual void vslot94(void);
	virtual void vslot98(void);
	virtual void vslot9C(void);
	virtual void vslotA0(void);
	virtual void vslotA4(void);
	virtual void vslotA8(void);
	virtual void vslotAC(void);
	virtual void vslotB0(void);
	virtual void vslotB4(void);
	virtual void vslotB8(void);
	virtual void vslotBC(void);
	virtual void vslotC0(void);
	virtual void vslotC4(void);
	virtual void vslotC8(void);
	virtual void vslotCC(void);
	virtual void vslotD0(void);
	virtual void vslotD4(void);
	virtual void vslotD8(void);
	virtual void vslotDC(void);
	virtual void vslotE0(void);
	virtual void vslotE4(void);
	virtual void vslotE8(AsciiString movieName, Int arg1, Int arg2);
	virtual void vslotEC(void);
	virtual Bool vslotF0(void);

	void bfmeStopMovie(void);                                             // 0x0040EFF0

	char m_pad004[0x111 - 0x004];
	Bool m_field111;                                                      // +0x111
	char m_pad112[0x138 - 0x112];
	Int m_field138;                                                       // +0x138
};

class GameWindowTransitionsHandler
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);

	void setGroup(AsciiString groupName, Bool immediate);
	void reverse(AsciiString groupName);
	Bool isFinished(void);
	void rva004893C0(void);                                               // sets +0x55
	void rva004893D0(void);                                               // clears +0x55
	void rva00489410(void);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

// Scoped guard: the constructor (0x00382960) and this inline destructor
// each poke TheTransitionHandler when it exists.
class Rva00382960
{
public:
	Rva00382960(void);
	~Rva00382960(void)
	{
		if (TheTransitionHandler)
			TheTransitionHandler->rva00489410();
	}
};

class WindowManager
{
public:
	void bfme_hideBackground(Bool hide);

	char m_pad000[0x1b8];
	Int m_field1B8;                                                       // +0x1B8
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(Bool visible);
};

class AudioManager
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void vslot08(void);
	virtual void vslot0C(void);
	virtual void vslot10(void);
	virtual void vslot14(void);
	virtual void vslot18(void);
	virtual void vslot1C(void);
	virtual void vslot20(void);
	virtual void vslot24(void);
	virtual void vslot28(void);
	virtual void vslot2C(void);
	virtual void vslot30(void);
	virtual void vslot34(void);
	virtual void vslot38(void);
	virtual void vslot3C(Int value);
};

class GlobalData
{
public:
	char m_pad000[0x1278];
	Bool m_field1278;                                                     // +0x1278
};

class TimedOperation;

// The by-value holder postTimedOp takes; built here from the group name.
class LoadGameFadeHolder
{
public:
	LoadGameFadeHolder(AsciiString name);                                 // 0x0038BD90
	LoadGameFadeHolder(const LoadGameFadeHolder &other);
	~LoadGameFadeHolder(void);

private:
	TimedOperation *m_value;
};

Bool postTimedOp(LoadGameFadeHolder holder, void *key);

class LoadScreen
{
public:
	virtual void vslot00(void);
	virtual void update(Int percent);
};

class GameLogic
{
public:
	Bool rva0038D100(void);
	void rva00382CC0(Int progress);                                       // m_loadScreen->update(progress)
	void destroyLoadScreen(void);                                         // 0x00382CE0

	char m_pad000[0x3c];
	UnsignedInt m_frame;                                                  // +0x3C
	char m_pad040[0x70 - 0x40];
	AsciiString m_string70;                                               // +0x70
	char m_pad074[0x94 - 0x74];
	Bool m_field94;                                                       // +0x94
	Bool m_field95;                                                       // +0x95
	char m_pad096[0x10c - 0x96];
	Int m_gameMode;                                                       // +0x10C
	char m_pad110[0x118 - 0x110];
	LoadScreen *m_loadScreen;                                             // +0x118
};

extern GameEngine *TheGameEngine;
extern NetworkInterface *TheNetwork;
extern GameLogic *TheGameLogic;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern WindowManager *g_theWindowManager;
extern Mouse *TheMouse;
extern AudioManager *TheAudio;
extern Real g_loadProgress12F089C;                                        // 0x012F089C
extern UnsignedInt g_fadeOpKey12ED588;                                    // 0x012ED588

// ?rva0038D100@GameLogic@@QAE_NXZ
Bool GameLogic::rva0038D100(void)
{
	if (!m_field94)
		return true;

	TheGameEngine->vslot40();

	if (TheNetwork && !TheNetwork->_bfme_isWaitingForPlayers())
	{
		Int mode = m_gameMode;
		if (mode == 2 || mode == 6 || mode == 1 || mode == 5)
		{
			UnsignedInt frame = TheGameLogic->m_frame;
			if (frame < 6)
			{
				if (frame >= 5)
				{
					if (m_loadScreen)
						m_loadScreen->update(100);
					return true;
				}
				rva00382CC0((Int)g_loadProgress12F089C);
				g_loadProgress12F089C += 0.25f;
				return true;
			}
		}
	}

	Bool restoreMouse = false;
	m_field94 = false;

	if (m_loadScreen && TheDisplay->vslotF0() && !TheWritableGlobalData->m_field1278)
	{
		if (m_field95)
		{
			{
				Rva00382960 guard;
				TheTransitionHandler->vslot10();
				TheTransitionHandler->setGroup("FadeWholeScreen", false);
				TheTransitionHandler->rva004893C0();
				TheTransitionHandler->vslot14();
			}
			while (TheDisplay->vslotF0() && TheDisplay->m_field138 < 100 && !TheTransitionHandler->isFinished())
			{
				TheGameEngine->vslot40();
				Sleep(1);
			}
			TheDisplay->bfmeStopMovie();
			TheTransitionHandler->reverse("FadeWholeScreen");
			TheTransitionHandler->vslot14();
			TheTransitionHandler->rva004893D0();
			m_field95 = false;
			restoreMouse = true;
		}
		else
		{
			switch (m_gameMode)
			{
				case 0:
				case 7:
					g_theWindowManager->bfme_hideBackground(true);
					if (m_string70.isNotEmpty())
					{
						TheTransitionHandler->setGroup("FadeWholeScreen", false);
						TheTransitionHandler->rva004893C0();
						while (TheDisplay->vslotF0() && TheDisplay->m_field138 < 100 && !TheTransitionHandler->isFinished())
						{
							TheGameEngine->vslot40();
							Sleep(5);
						}
						destroyLoadScreen();
						if (m_string70.isNotEmpty())
						{
							TheDisplay->vslotE8(m_string70, 1, 0x30);
							{
								AsciiString fadeGroup("FadeWholeScreen");
								postTimedOp(fadeGroup, &g_fadeOpKey12ED588);
							}
							m_string70.clear();
						}
						else
						{
							TheDisplay->vslotEC();
							TheTransitionHandler->rva004893D0();
						}
					}
					else
					{
						TheDisplay->vslotEC();
						TheTransitionHandler->rva004893D0();
						restoreMouse = true;
					}
					break;

				case 2:
				case 3:
				case 6:
					TheTransitionHandler->setGroup("FadeWholeScreen", false);
					TheTransitionHandler->rva004893C0();
					TheTransitionHandler->vslot14();
					while (TheDisplay->vslotF0() && TheDisplay->m_field138 < 100 && !TheTransitionHandler->isFinished())
					{
						TheGameEngine->vslot40();
						Sleep(5);
					}
					{
						AsciiString fadeGroup("FadeWholeScreen");
						postTimedOp(fadeGroup, &g_fadeOpKey12ED588);
					}
					TheTransitionHandler->vslot14();
					break;

				case 4:
					TheTransitionHandler->vslot10();
					if (!g_theWindowManager || !g_theWindowManager->m_field1B8)
					{
						TheTransitionHandler->setGroup("FadeWholeScreen", false);
						TheTransitionHandler->vslot14();
						while (TheDisplay->vslotF0() && TheDisplay->m_field138 < 100 && !TheTransitionHandler->isFinished())
						{
							TheGameEngine->vslot40();
							Sleep(1);
						}
					}
					restoreMouse = true;
					break;

				default:
					TheDisplay->vslotEC();
					TheTransitionHandler->rva004893D0();
					restoreMouse = true;
					break;
			}
		}
	}
	else
	{
		restoreMouse = true;
	}

	if (m_loadScreen)
		destroyLoadScreen();
	if (restoreMouse)
		TheMouse->_bfme_setEngineVisibility(true);
	TheDisplay->m_field111 = false;
	TheGameEngine->vslot40();
	if (TheAudio)
		TheAudio->vslot3C(0);
	return true;
}
