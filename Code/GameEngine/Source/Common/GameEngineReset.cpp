// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
// readable body of ?reset@GameEngine@@UAEXXZ: Code/GameEngine/Source/Common/GameEngine.cpp

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef unsigned int UnsignedInt;
typedef int Bool;
typedef void *HANDLE;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	UnsignedInt winClearStatus(UnsignedInt status);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void slot00(void);
	virtual ~WindowLayout();
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void hide(Bool hide);
	virtual void bringForward(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void destroyWindows(void);

	char m_unknown04[4];
	GameWindow *m_firstWindow;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual WindowLayout *winCreateLayout(AsciiString filename);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_unknown00[0x10C];
	int m_gameMode;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterfaceList
{
public:
	void resetAll(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual ~NetworkInterface();
};

class Rva00065A40
{
public:
	void forward(void);
};

void InitGameLogicRandom(UnsignedInt seed);

#define TheWindowManager (*(GameWindowManager **)0x012F1B40)
#define TheGameLogic (*(GameLogic **)0x012F0898)
#define TheSubsystemList (*(SubsystemInterfaceList **)0x0134C6C8)
#define TheNetwork (*(NetworkInterface **)0x012F7714)
#define ResetSink (*(Rva00065A40 **)0x012ED4FC)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void reset(void);

private:
	void _bfme_terminateChildProcesses(void);

	char m_unknown04[0x0C];
	int m_childProcessCount;
	HANDLE m_childProcesses[7];
	int m_clientFramePeriod;
	int m_clientFrameCounter;
	float m_clientFrameRatio;
	bool m_clientFrameRatioPending;
	char m_unknown3D[3];
	float m_clientFrameLimit;
	UnsignedInt m_metric44;
	UnsignedInt m_metric48;
	UnsignedInt m_metric4C;
	UnsignedInt m_metric50;
	UnsignedInt m_metric54;
	UnsignedInt m_metric58;
};

void GameEngine::reset(void)
{
	WindowLayout *background =
		TheWindowManager->winCreateLayout(AsciiString("Menus/BlankWindow.wnd"));
	background->hide(false);
	background->bringForward();
	background->m_firstWindow->winClearStatus(0x80);

	bool deleteNetwork = false;
	if (TheGameLogic->m_gameMode == 1 || TheGameLogic->m_gameMode == 5)
		deleteNetwork = true;

	InitGameLogicRandom(0);
	TheSubsystemList->resetAll();

	if (deleteNetwork)
	{
		delete TheNetwork;
		TheNetwork = 0;
	}

	background->destroyWindows();
	delete background;

	_bfme_terminateChildProcesses();
	m_clientFrameRatioPending = false;
	m_clientFrameCounter = 6;
	m_clientFrameLimit = 6.0f;
	m_metric44 = 0;
	if (ResetSink != 0)
		ResetSink->forward();
	m_metric48 = 0;
	m_metric54 = 0;
	m_metric4C = 0;
	m_metric58 = 0;
	m_metric50 = timeGetTime();
}
