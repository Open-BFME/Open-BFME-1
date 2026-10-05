// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "dx8wrapper.h"

// Open-BFME5 conversions.

class BfmeT1057
{
public:
	virtual void bfmeVT01057();
	virtual void bfmeVT11057();
	virtual void bfmeVT21057();
	virtual void bfmeVT31057();
	virtual void bfmeVT41057();
	virtual void bfmeVT51057();
	virtual void bfmeVT61057();
	virtual void bfmeVT71057();
	virtual void bfmeVT81057();
	virtual void bfmeVT91057();
	virtual void bfmeVT101057();
	virtual void bfmeVT111057();
	virtual void bfmeVT121057();
	virtual void bfmeVT131057();
	virtual void bfmeVT141057();
	virtual void bfmeVT151057();
	virtual void bfmeVT161057();
	virtual void bfmeVT171057();
	virtual void bfmeVT181057();
	virtual void bfmeVT191057();
	virtual void bfmeVT201057();
	virtual void bfmeVT211057();
	virtual void bfmeVT221057();
	virtual void bfmeVT231057();
	virtual void bfmeVT241057();
	virtual void bfmeVT251057();
	virtual int bfmeNow1057();
};

// This reference is the global at 0x012F1464, EA's
// `GameClient *TheGameClient` (?TheGameClient@@3PAVGameClient@@A, defined in
// game/GameEngine/Source/GameClient/GameClient.cpp); BfmeT1057 is this TU's
// view of it and is reached through a cast.
class GameClient;
extern GameClient *TheGameClient;
static inline BfmeT1057 *theGameClientView() { return (BfmeT1057 *)TheGameClient; }

class BfmeA1057
{
public:
	void bfmeGo1057A(int a);

	char m_bfmePad[0xb0];
	volatile int m_bfmeb0;
	char m_bfmePad2[0x70];
	volatile int m_bfme124;
	volatile int m_bfme128;
	volatile int m_bfme12c;
	char m_bfmePad3[0x1d8];
	volatile int m_bfme308;
};

void BfmeA1057::bfmeGo1057A(int a)
{
	int z = 0;

	m_bfmeb0 = z;
	m_bfme124 = 1;
	m_bfme12c = a;
	m_bfme128 = z;
	m_bfme308 = theGameClientView()->bfmeNow1057();
}

class BfmeLog1057
{
public:
	void bfmeLog1057(int a, char *f, int n, char *t, int p, int q, int r, int s);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the log() through it, so the pointee stays the local BfmeLog1057 view and the
// access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

struct BfmeP1057
{
	char m_bfmePad[0x250];
	int m_bfmeId;
};

class BfmeB1057
{
public:
	void bfmeGo1057B(int unused);

	char m_bfmePad[0x34];
	BfmeP1057 *m_bfmeP;
	char m_bfmePad2[0x150];
	int m_bfmeState;
	char m_bfmePad3[0x28];
	char m_bfmeFlag;
};

void BfmeB1057::bfmeGo1057B(int unused)
{
	((BfmeLog1057 *)g_rva012F19E8WindowManager)->bfmeLog1057(m_bfmeP->m_bfmeId, "CallChild", 1, "ClosePassword", 0, 0, 0, 0);
	m_bfmeState = 1;
	m_bfmeFlag = 0;
}

struct BfmeVt1057
{
	char m_bfmePad[0x114];
	void (__stdcall *m_bfmeFn)(void *o, int a, int b, int c);
};

struct BfmeE1057
{
	BfmeVt1057 *m_bfmeVt;
};

extern unsigned int number_of_DX8_calls;
extern int g_bfmeB1057;

void bfmeGo1057C(int a, int b, int c)
{
	BfmeE1057 *p = reinterpret_cast<BfmeE1057 *>(DX8Wrapper::_Get_D3D_Device8());

	p->m_bfmeVt->m_bfmeFn(p, a, b, c);
	number_of_DX8_calls++;
	g_bfmeB1057++;
}

