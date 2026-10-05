// Open-BFME5 conversions.

class BfmeX1073;

class BfmeR1073
{
public:
	void bfmeRun1073(BfmeX1073 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// Retail's first-argument global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).
// The TU-local BfmeX1073 view is only a call-target type here, so the canonical
// int is cast to it at the use; the load is `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;
static inline BfmeX1073 *bfmeX1073()
{
	return (BfmeX1073 *)g_aptPalantirWindow;
}
extern char g_bfmeFmtA1073[];
extern char g_bfmeFmtB1073[];
extern char g_bfmeLit1073[];

class BfmeQ1073
{
public:
	void bfmeGo1073A(char a);
	char m_bfmePad[0x250];
	BfmeX1073 *m_bfme250;
	char m_bfmePad1[0x180];
	int m_bfme3d4;
};

void BfmeQ1073::bfmeGo1073A(char a)
{
	if ((a & 1) && (m_bfme3d4 & 1)) {
		((BfmeR1073 *)g_rva012F19E8WindowManager)->bfmeRun1073(m_bfme250, g_bfmeFmtA1073, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 &= ~1;
	}
	if ((a & 2) && (m_bfme3d4 & 2)) {
		((BfmeR1073 *)g_rva012F19E8WindowManager)->bfmeRun1073(m_bfme250, g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 &= ~2;
	}
}

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *b, unsigned int n, char *f, double d);

struct BfmeN1073
{
	char *m_bfme00;
};

void bfmeGo1073B(BfmeN1073 *n, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char *q;
	char *s;

	_snprintf(buf1, 0x10, "%g", b);
	_snprintf(buf2, 0x10, "%g", c);
	q = n->m_bfme00;
	s = q ? q + 8 : g_bfmeLit1073;
	((BfmeR1073 *)g_rva012F19E8WindowManager)->bfmeRun1073(bfmeX1073(), "MoveButtonFlash", 3, s, buf1, buf2, 0, 0);
}
