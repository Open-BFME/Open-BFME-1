// Open-BFME5 conversions.

struct BfmeP1060
{
	char m_bfmePad[0x54];
	volatile int m_bfme54;
};

extern BfmeP1060 *g_bfmeP1060;
extern char g_bfmeLitA1060[];
extern char g_bfmeLitB1060[];
extern char g_bfmeLitC1060[];

class BfmeX1060;

// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the level-path builder's window argument, so
// the int is cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;

class BfmeR1060;

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. BfmeR1060 is this
// TU's forward-declared view of the pointee; cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

// The APT/level-path builder the call below reaches (retail 0x004675F0) is a
// member of the level-path builder class; BfmeLevelAN is this TU's view of the
// pointee, as in BfmeConv924.cpp.  The casts at the use are pointer-size
// neutral.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
		int p7, int p8);
};

void bfmeGo1060B(void)
{
	int v = g_bfmeP1060->m_bfme54;
	char *s = --v ? g_bfmeLitA1060 : g_bfmeLitB1060;

	((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)g_aptPalantirWindow,
		(int)g_bfmeLitC1060, 1, (int)s, 0, 0, 0, 0);
}

class BfmeO1060
{
public:
	int bfmeGet1060(int a);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
enum NameKeyType { };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *a);
};

extern NameKeyGenerator *g_bfmeQ1060;

struct BfmeFn1060
{
	void (__cdecl *m_bfmeFn)(BfmeO1060 *a, int b, int c, int d);
};

class BfmeSub1060
{
public:
	BfmeFn1060 *bfmeFind1060(int *k);
};

class BfmeW1060
{
public:
	char m_bfmePad[8];
	BfmeSub1060 m_bfmeSub;
};

extern BfmeW1060 *g_bfmeW1060;

void bfmeGo1060D(BfmeO1060 *o, int b, int c, int d)
{
	// The stand-in bfmeGet1060 returns the name pointer; its int spelling is
	// TU-local, so cast at the call and keep the pushed bytes identical.
	int t = (int)g_bfmeQ1060->nameToKey((const char *)o->bfmeGet1060(0));

	g_bfmeW1060->m_bfmeSub.bfmeFind1060(&t)->m_bfmeFn(o, b, c, d);
}
