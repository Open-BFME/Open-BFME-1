// Open-BFME5 conversions.

class BfmeX1067;

class BfmeR1067
{
public:
	void bfmeRun1067(BfmeX1067 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the run() through it, so the pointee stays the local BfmeR1067 view and the
// access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
extern BfmeX1067 *g_bfmeV1067;

// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the run() interface argument, so the int is
// cast at the use and the pushed bytes stay identical.  g_bfmeV1067 is a
// different global (0x012F49A8) and keeps its own name.
extern int g_aptPalantirWindow;
extern char g_bfmeFmtD1067[];
extern char g_bfmeFmtA1067[];
extern char g_bfmeFmtB1067[];
extern char g_bfmeLit1067[];
extern char g_bfmeLitA1067[];
extern char g_bfmeLitB1067[];

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *b, unsigned int n, char *f, int a);
BfmeX1067 *__cdecl bfmeMk1067(BfmeX1067 *a, BfmeX1067 *b);

struct BfmeN1067
{
	char *m_bfme00;
};

void bfmeGo1067A(int a, BfmeN1067 *n)
{
	char buf[0x10];
	char *q;
	char *s;

	_snprintf(buf, 0x10, g_bfmeFmtD1067, a);
	q = n->m_bfme00;
	s = q ? q + 8 : g_bfmeLit1067;
	((BfmeR1067 *)g_rva012F19E8WindowManager)->bfmeRun1067((BfmeX1067 *)g_aptPalantirWindow, g_bfmeFmtA1067, 2, buf, s, 0, 0, 0);
}

void bfmeGo1067B(int a, char b)
{
	char buf[0x10];
	char *s;

	_snprintf(buf, 0x10, g_bfmeFmtD1067, a);
	s = b ? g_bfmeLitA1067 : g_bfmeLitB1067;
	((BfmeR1067 *)g_rva012F19E8WindowManager)->bfmeRun1067(bfmeMk1067(g_bfmeV1067, g_bfmeV1067), g_bfmeFmtB1067, 2, buf, s, 0, 0, 0);
}
