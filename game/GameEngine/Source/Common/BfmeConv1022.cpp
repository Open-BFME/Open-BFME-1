// Open-BFME5 conversions.

struct BfmeElem1022
{
	void *m_bfmeP;
	char m_bfmePad[0x14];
};

struct BfmeTab1022
{
	char m_bfmePad[0x1c];
	BfmeElem1022 m_bfmeItems[1];
};

// The global this TU reaches at 0x012F33F8 is EA's control-bar singleton
// `ControlBar *TheControlBar' (?TheControlBar@@3PAVControlBar@@A), defined
// once in GameClient/GUI/ControlBar/ControlBar.cpp, and the drop it performs
// is retail's ControlBar body at 0x004C1B60, reached through the ILT thunk
// 0x0003BCCD and matched as ControlBar::rva004C1B60. Only the slot called here
// is modelled; the view is this TU's own ABI of it, so the cast at the use is
// a no-op and the bytes are unchanged.
//
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class GameWindow;

class ControlBar
{
public:
	void rva004C1B60(GameWindow *window, void *item);
};

extern ControlBar *TheControlBar;			// retail 0x012F33F8

class BfmeD1022
{
public:
	void bfmeGo1022D(int unused);

	BfmeTab1022 *m_bfmeTab;
	int m_bfmeIdx;
};

void BfmeD1022::bfmeGo1022D(int unused)
{
	void *p = m_bfmeTab->m_bfmeItems[m_bfmeIdx].m_bfmeP;

	if (p != 0)
		TheControlBar->rva004C1B60(0, p);
}

class BfmeG1022
{
public:
	virtual void bfmeVG01022();
	virtual void bfmeVG11022();
	virtual void bfmeVG21022();
	virtual void bfmeVG31022();
	virtual void bfmeVG41022();
	virtual void bfmeVG51022();
	virtual void bfmeVG61022();
	virtual void bfmeVG71022();
	virtual void bfmeVG81022();
	virtual void bfmeVG91022();
	virtual void bfmeVG101022();
	virtual void bfmeVG111022();
	virtual void bfmeVG121022();
	virtual void bfmeVG131022();
	virtual void bfmeVG141022();
	virtual void bfmeVG151022();
	virtual void bfmeVG161022();
	virtual void bfmeVG171022();
	virtual void bfmeVG181022();
	virtual void bfmeKill1022(int h);
};

// The retail global at 0x012ED668 is EA's AudioManager *TheAudio, defined once
// in game/GameEngine/Source/Common/Audio/GameAudio.cpp.  This TU keeps its own
// address-derived view of that object and casts at the use, so the reference
// names the one linked global.
class AudioManager;
extern AudioManager *TheAudio;
static inline BfmeG1022 *localAudio() { return (BfmeG1022 *)TheAudio; }

class BfmeF1022
{
public:
	int bfmeGo1022F(void);

	char m_bfmePad[0x1c];
	int m_bfmeH;
};

int BfmeF1022::bfmeGo1022F(void)
{
	if (localAudio() != 0) {
		localAudio()->bfmeKill1022(m_bfmeH);
		m_bfmeH = 1;
	}

	return 0x3fffffff;
}

class BfmeN1022
{
public:
	virtual void bfmeVN01022();
	virtual void bfmeVN11022();
	virtual void bfmeVN21022();
	virtual void bfmeVN31022();
	virtual void bfmeVN41022();
	virtual void bfmeVN51022();
	virtual void bfmeVN61022();
	virtual void bfmeVN71022();
	virtual void bfmeVN81022();
	virtual void bfmeVN91022();
	virtual void bfmeVN101022();
	virtual void bfmeVN111022();
	virtual void bfmeVN121022();
	virtual void bfmeVN131022();
	virtual void bfmeVN141022();
	virtual void bfmeVN151022();
	virtual void bfmeVN161022();
	virtual void bfmeVN171022();
	virtual void bfmeVN181022();
	virtual void bfmeVN191022();
	virtual void bfmeVN201022();
	virtual void bfmeVN211022();
	virtual void bfmeVN221022();
	virtual void bfmeVN231022();
	virtual void bfmeVN241022();
	virtual void bfmeVN251022();
	virtual void bfmeVN261022();
	virtual void bfmeVN271022();
	virtual void bfmeVN281022();
	virtual void bfmeVN291022();
	virtual void bfmeVN301022();
	virtual void bfmeVN311022();
	virtual void bfmeVN321022();
	virtual void bfmeVN331022();
	virtual void bfmeVN341022();
	virtual void bfmeVN351022();
	virtual void bfmeVN361022();
	virtual void bfmeVN371022();
	virtual void bfmeVN381022();
	virtual void bfmeVN391022();
	virtual void bfmeVN401022();
	virtual void bfmeVN411022();
	virtual void bfmeVN421022();
	virtual void bfmeVN431022();
	virtual void bfmeReg1022(void *p);
	virtual void bfmeVN451022();
	virtual void bfmeVN461022();
	virtual void bfmeVN471022();
	virtual void bfmeVN481022();
	virtual void bfmeVN491022();
	virtual void bfmeVN501022();
	virtual void bfmeVN511022();
	virtual void bfmeVN521022();
	virtual void bfmeQuery1022(int h, int k, int f, int *out);
};

// The global read at 0x012F1B40 is EA's window-manager singleton, spelled in
// exactly one name everywhere in the link: `GameWindowManager *TheWindowManager'
// (?TheWindowManager@@3PAVGameWindowManager@@A), defined in
// game/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp. The class above
// is this TU's local ABI view of the slots it calls, cast to at the use; the cast
// is a no-op, so the bytes are unchanged.
class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class BfmeI1022
{
public:
	void bfmeGo1022I(void);

	char m_bfmePad[0x50];
	void *m_bfmeP;
	char m_bfmePad2[0x44];
	char m_bfmeDone;
};

void BfmeI1022::bfmeGo1022I(void)
{
	if (m_bfmeDone == 0) {
		m_bfmeDone = 1;
		((BfmeN1022 *)TheWindowManager)->bfmeReg1022(m_bfmeP);
	}
}

// The global this TU reaches at 0x012F7198 is retail's staging-room pointer
// `GameSpyStagingRoom *TheGameSpyGame'
// (?TheGameSpyGame@@3PAVGameSpyStagingRoom@@A), so the type is named with its
// defining spelling to keep the extern's mangled name exact; only the slots
// this body calls are modelled, and their names are address-derived.
class GameSpyStagingRoom
{
public:
	virtual void bfmeVK01022();
	virtual void bfmeVK11022();
	virtual void bfmeVK21022();
	virtual void bfmeSend1022(int n);
};

extern GameSpyStagingRoom *TheGameSpyGame;

class BfmeJ1022
{
public:
	void bfmeGo1022J(int unused);

	char m_bfmePad[0x3c];
	int m_bfmeState;
	char m_bfmePad2[0x16];
	char m_bfmeFlag;
};

void BfmeJ1022::bfmeGo1022J(int unused)
{
	m_bfmeState = 2;

	if (m_bfmeFlag != 0) {
		m_bfmeFlag = 0;
		TheGameSpyGame->bfmeSend1022(0);
	}
}

int bfmeGo1022L(int h)
{
	if (h == 0)
		return -1;

	((BfmeN1022 *)TheWindowManager)->bfmeQuery1022(h, 0x402b, 0, &h);
	return h;
}
