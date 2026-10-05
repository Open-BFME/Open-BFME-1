// Open-BFME5 conversions.

class BfmeX1071;

class BfmeR1071
{
public:
	void bfmeRun1071(BfmeX1071 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
	void bfmeOpen1071(BfmeX1071 *a);
};

// The global at 0x012F19E8 is EA's
// `WindowManager *g_rva012F19E8WindowManager` (defined in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp); BfmeR1071 is this
// TU's view of the same object, so the uses cast.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the run() interface argument, so the int is
// cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;

extern char g_bfmeFmtD1071[];
extern char g_bfmeFmtP1071[];
extern char g_bfmeFmtQ1071[];
extern char g_bfmeFmtR1071[];
extern unsigned char g_aptPalantirClosed;
extern unsigned char g_aptPalantirCloseRequested;

extern "C" __declspec(dllimport) int __cdecl sprintf(char *b, char *f, int a);

void bfmeGo1071A(int a, char b)
{
	char buf[0x10] = "";

	sprintf(buf, g_bfmeFmtD1071, a);
	((BfmeR1071 *)g_rva012F19E8WindowManager)->bfmeRun1071((BfmeX1071 *)g_aptPalantirWindow, b ? g_bfmeFmtP1071 : g_bfmeFmtQ1071, 1, buf, 0, 0, 0, 0);
}

void bfmeGo1071B(char a)
{
	if (a) {
		if (!g_aptPalantirClosed) {
			g_aptPalantirCloseRequested = 1;
			((BfmeR1071 *)g_rva012F19E8WindowManager)->bfmeOpen1071((BfmeX1071 *)g_aptPalantirWindow);
			g_aptPalantirClosed = 1;
			g_aptPalantirCloseRequested = 0;
		}
	} else {
		if (!g_aptPalantirClosed && !g_aptPalantirCloseRequested) {
			((BfmeR1071 *)g_rva012F19E8WindowManager)->bfmeRun1071((BfmeX1071 *)g_aptPalantirWindow, g_bfmeFmtR1071, 0, 0, 0, 0, 0, 0);
			g_aptPalantirCloseRequested = 1;
		}
	}
}
