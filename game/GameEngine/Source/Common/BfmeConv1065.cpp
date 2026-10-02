// Open-BFME5 conversions.

class BfmeX1065;

struct BfmeFl1065
{
	char m_bfmePad[4];
	float m_bfme04;
};

class BfmeR1065
{
public:
	virtual void bfmeSlot1065R_0(void);
	virtual void bfmeSlot1065R_1(void);
	virtual void bfmeSlot1065R_2(void);
	virtual void bfmeSlot1065R_3(void);
	virtual void bfmeSlot1065R_4(void);
	virtual void bfmeSlot1065R_5(void);
	virtual void bfmeSlot1065R_6(void);
	virtual void bfmeSlot1065R_7(void);
	virtual void bfmeSlot1065R_8(void);
	virtual void bfmeSlot1065R_9(void);
	virtual void bfmeSlot1065R_10(void);
	virtual BfmeFl1065 * bfmeSlot1065R_11(void);
	void bfmeRun1065(BfmeX1065 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the run()/slot calls through it, so the pointee stays the local BfmeR1065 view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
// The global at 0x012B7D80 is EA's `int g_aptPalantirWindow` (defined once in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp). This
// TU only pushes its address as the run() interface argument, so the int is
// cast at the use and the pushed bytes stay identical.
extern int g_aptPalantirWindow;
extern char g_bfmeFmtD1065[];
extern char g_bfmeFmtF1065[];
extern char g_bfmeFmtG1065[];
extern char g_bfmeFmtH1065[];
extern char *g_bfmeTbl1065[];

class BfmeH1065;

extern "C" __declspec(dllimport) int __cdecl sprintf(char *b, char *f, int a);
BfmeX1065 *__cdecl bfmeConv1065(BfmeH1065 *h);

class BfmeH1065
{
public:
	void bfmeGo1065B(int a, int b);
};

void BfmeH1065::bfmeGo1065B(int a, int b)
{
	sprintf((char *)&a, g_bfmeFmtD1065, a + 1);
	((BfmeR1065 *)g_rva012F19E8WindowManager)->bfmeRun1065(bfmeConv1065(this), g_bfmeFmtF1065, 2, (char *)&a,
		g_bfmeTbl1065[b], 0, 0, 0);
}

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *b, unsigned int n, char *f, double d);

void bfmeGo1065C(int a)
{
	char buf[0x10];

	_snprintf(buf, 0x10, g_bfmeFmtG1065, a * ((BfmeR1065 *)g_rva012F19E8WindowManager)->bfmeSlot1065R_11()->m_bfme04);
	((BfmeR1065 *)g_rva012F19E8WindowManager)->bfmeRun1065((BfmeX1065 *)g_aptPalantirWindow, g_bfmeFmtH1065, 1, buf, 0, 0, 0, 0);
}
