// Open-BFME5 conversions.

class BfmeX1068;

class BfmeR1068
{
public:
	void bfmeRun1068(BfmeX1068 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the run() through it, so the pointee stays the local BfmeR1068 view and the
// access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the run() interface argument, so the int is
// cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;
extern char g_bfmeFmtD1068[];
extern char g_bfmeFmtA1068[];
extern char g_bfmeFmtB1068[];

extern "C" __declspec(dllimport) int __cdecl sprintf(char *b, char *f, int a);

void bfmeGo1068A(int a, int b)
{
	int v = b;

	if (!v)
		v = 1;
	sprintf((char *)&b, g_bfmeFmtD1068, a + 1);
	sprintf((char *)&a, g_bfmeFmtD1068, v);
	((BfmeR1068 *)g_rva012F19E8WindowManager)->bfmeRun1068((BfmeX1068 *)g_aptPalantirWindow, g_bfmeFmtA1068, 2, (char *)&b, (char *)&a, 0, 0, 0);
}

void bfmeGo1068B(int a, int b)
{
	int v = b;

	if (!v)
		v = 1;
	sprintf((char *)&b, g_bfmeFmtD1068, a + 1);
	sprintf((char *)&a, g_bfmeFmtD1068, v);
	((BfmeR1068 *)g_rva012F19E8WindowManager)->bfmeRun1068((BfmeX1068 *)g_aptPalantirWindow, g_bfmeFmtB1068, 2, (char *)&b, (char *)&a, 0, 0, 0);
}
