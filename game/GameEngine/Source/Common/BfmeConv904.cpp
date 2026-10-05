// Open-BFME5 conversions.

struct BfmeSlotMA
{
	int m_bfmeVal;
	char m_bfmePad[0x14];
};

class BfmeThingMA
{
public:
	char bfmeGoMA(int i);
	char m_bfmePad[0x2bc];
	int m_bfmeCur;
	BfmeSlotMA m_bfmeArr[17];
};

char BfmeThingMA::bfmeGoMA(int i)
{
	if (i >= 0 && i < 0x11)
		return (char)(m_bfmeArr[i].m_bfmeVal != m_bfmeCur);
	return 0;
}

class BfmeGlobMB
{
public:
	void bfmeDoMB(int f, void *p);
};

class ControlBar;
extern ControlBar *TheControlBar;

struct BfmeSlotMB
{
	void *m_bfmeP;
	char m_bfmePad[0x14];
};

struct BfmeTabMB
{
	char m_bfmePad[0x1c];
	BfmeSlotMB m_bfmeArr[1];
};

class BfmeThingMB
{
public:
	void bfmeGoMB(void *a);
	char m_bfmePad[8];
	BfmeTabMB *m_bfmeTab;
	int m_bfmeIdx;
};

void BfmeThingMB::bfmeGoMB(void *a)
{
	void *p = m_bfmeTab->m_bfmeArr[m_bfmeIdx].m_bfmeP;
	if (p)
		reinterpret_cast<BfmeGlobMB *>(TheControlBar)->bfmeDoMB(0, p);
}

class BfmeGlobMC
{
public:
	virtual void bfmeSlotMC00();
	virtual void bfmeSlotMC01();
	virtual void bfmeSlotMC02();
	virtual void bfmeSlotMC03();
	virtual void bfmeSlotMC04();
	virtual void bfmeSlotMC05();
	virtual void bfmeSlotMC06();
	virtual void bfmeSlotMC07();
	virtual void bfmeSlotMC08();
	virtual void bfmeSlotMC09();
	virtual void bfmeSlotMC10();
	virtual void bfmeSlotMC11();
	virtual void bfmeSlotMC12();
	virtual void bfmeSlotMC13();
	virtual void bfmeSlotMC14();
	virtual void bfmeSlotMC15();
	virtual void bfmeSlotMC16();
	virtual void bfmeSlotMC17();
	virtual void bfmeSlotMC18();
	virtual void bfmeSlotMC19();
	virtual void bfmeSlotMC20();
	virtual void bfmeSlotMC21();
	virtual void bfmeSlotMC22();
	virtual void bfmeSlotMC23();
	virtual void bfmeSlotMC24();
	virtual void bfmeSlotMC25();
	virtual void bfmeSlotMC26();
	virtual void bfmeSlotMC27();
	virtual void bfmeSlotMC28();
	virtual void bfmeSlotMC29();
	virtual void bfmeSlotMC30();
	virtual void bfmeSlotMC31();
	virtual void bfmeSlotMC32();
	virtual void bfmeSlotMC33();
	virtual void bfmeSlotMC34();
	virtual void bfmeSlotMC35();
	virtual void bfmeSlotMC36();
	virtual void bfmeSlotMC37();
	virtual void bfmeSlotMC38();
	virtual void bfmeSlotMC39();
	virtual void bfmeSlotMC40();
	virtual void bfmeSlotMC41();
	virtual void bfmeSlotMC42();
	virtual void bfmeSlotMC43();
	virtual bool bfmeCheckMC(void *a);
};

// Retail's audio global, at 0x012ED668, is AudioManager *TheAudio
// (?TheAudio@@3PAVAudioManager@@A). The BfmeGlobMC view above is TU-local.
class AudioManager;
extern AudioManager *TheAudio;

class BfmeThingMC
{
public:
	int bfmeGoMC();
	char m_bfmePad[0x64];
	void *m_bfmeArg;
};

int BfmeThingMC::bfmeGoMC()
{
	if (TheAudio) {
		if (((BfmeGlobMC *)TheAudio)->bfmeCheckMC(m_bfmeArg))
			return 1;
	}
	return 0;
}

class BfmeObjMD
{
public:
	void bfmeOneMD(int v);
	void bfmeTwoMD();
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern unsigned char g_aptPalantirCallbacksRegistered;
// Retail global 0x012B7D80: the AptPalantir window index, `int
// g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).  The
// type already matches, so this is a pure respelling: the use needs no cast.
extern int g_aptPalantirWindow;

void bfmeGoMD(void)
{
	if (g_aptPalantirCallbacksRegistered) {
		((BfmeObjMD *)g_rva012F19E8WindowManager)->bfmeOneMD(g_aptPalantirWindow);
		((BfmeObjMD *)g_rva012F19E8WindowManager)->bfmeTwoMD();
	}
}

class BfmeThingME
{
public:
	void bfmeGoME(int a);
	int bfmeTestME();
	void bfmeActME();
	char m_bfmePad[0x258];
	int m_bfmeState;
};

void BfmeThingME::bfmeGoME(int a)
{
	if (bfmeTestME() == 0) {
		bfmeActME();
		return;
	}
	m_bfmeState = 0xb;
}

class BfmeSubMF
{
public:
	void bfmeTailMF(int f);
};

class BfmeThingMF
{
public:
	void bfmeGoMF(int f);
	char m_bfmePad[0x310];
	BfmeSubMF *m_bfmeSub;
	char m_bfmePad2[4];
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeThingMF::bfmeGoMF(int f)
{
	m_bfmeA = 0;
	m_bfmeB = -1;
	if (m_bfmeSub)
		m_bfmeSub->bfmeTailMF(1);
}

class BfmeObjMG
{
public:
	void bfmeDoMG();
};

extern int g_bfmePeerReqE8;
extern int g_bfmePeerReqE4;
extern int g_bfmeFlagMG;

void __stdcall bfmeGoMG(int a)
{
	g_bfmePeerReqE8 = -1;
	g_bfmePeerReqE4 = -1;
	if (g_bfmeFlagMG)
		((BfmeObjMG *)g_rva012F19E8WindowManager)->bfmeDoMG();
}
