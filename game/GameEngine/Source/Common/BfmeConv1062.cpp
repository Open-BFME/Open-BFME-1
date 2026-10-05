// Open-BFME5 conversions.

class BfmeA1062
{
public:
	void bfmeF1062A(void);
};

class BfmeB1062
{
public:
	void bfmeF1062B(void);
};

extern BfmeA1062 *g_bfmeA1062;
extern BfmeB1062 *g_bfmeB1062;

void bfmeGo1062A(void)
{
	if (g_bfmeA1062)
		g_bfmeA1062->bfmeF1062A();
	if (g_bfmeB1062)
		g_bfmeB1062->bfmeF1062B();
}

class BfmeC1062
{
public:
	virtual void bfmeSlot1062C_0(void);
	virtual void bfmeSlot1062C_1(void);
};

extern BfmeC1062 *g_bfmeC1062;
extern BfmeC1062 *g_bfmeD1062;

void bfmeGo1062B(void)
{
	if (g_bfmeC1062) {
		g_bfmeC1062->bfmeSlot1062C_1();
		g_bfmeC1062 = 0;
	}
	if (g_bfmeD1062) {
		g_bfmeD1062->bfmeSlot1062C_1();
		g_bfmeD1062 = 0;
	}
}

struct BfmeP1062
{
	char m_bfmePad[0x50];
	int m_bfme50;
};

extern BfmeP1062 *g_bfmeP1062;
extern char g_bfmeLit1_1062[];
extern char g_bfmeLit3_1062[];

class BfmeX1062;

// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the run() interface argument, so the int is
// cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;

class BfmeR1062
{
public:
	void bfmeRun1062(BfmeX1062 *a, char *b, int c, char *d, int e, int f, int g, int h);
};

// Retail's WindowManager global at 0x012F19E8, under the one linked-build
// spelling.  BfmeR1062 above is this TU's view of the same object.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

static inline BfmeR1062 *bfmeR1062View(void)
{
	return (BfmeR1062 *)g_rva012F19E8WindowManager;
}

void bfmeGo1062D(void)
{
	char *s;

	switch (g_bfmeP1062->m_bfme50) {
		case 1:
			s = g_bfmeLit1_1062;
			break;
		case 2:
			s = "_selected";
			break;
		default:
			s = g_bfmeLit3_1062;
			break;
	}
	bfmeR1062View()->bfmeRun1062((BfmeX1062 *)g_aptPalantirWindow, "UpdateSkillUpgradeButton", 1, s, 0, 0, 0, 0);
}
