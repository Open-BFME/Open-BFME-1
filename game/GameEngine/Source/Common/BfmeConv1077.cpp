// Open-BFME5 conversions.

class BfmeX1077;

struct BfmeFl1077
{
	float m_bfme00;
	float m_bfme04;
};

class BfmeR1077
{
public:
	virtual void bfmeSlot1077R_0(void);
	virtual void bfmeSlot1077R_1(void);
	virtual void bfmeSlot1077R_2(void);
	virtual void bfmeSlot1077R_3(void);
	virtual void bfmeSlot1077R_4(void);
	virtual void bfmeSlot1077R_5(void);
	virtual void bfmeSlot1077R_6(void);
	virtual void bfmeSlot1077R_7(void);
	virtual void bfmeSlot1077R_8(void);
	virtual void bfmeSlot1077R_9(void);
	virtual void bfmeSlot1077R_10(void);
	virtual BfmeFl1077 * bfmeSlot1077R_11(void);
	void bfmeRun1077(BfmeX1077 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail's manager global at 0x012F19E8 is EA's WindowManager singleton (defined
// in GameClient/GUI/WindowManager.cpp); the TU-local BfmeR1077 view above is
// reached by casting the canonical global.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
// Retail's first-argument global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).
// The TU-local BfmeX1077 view is only a call-target type here, so the canonical
// int is cast to it at the use; the load is `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;
static inline BfmeX1077 *bfmeX1077()
{
	return (BfmeX1077 *)g_aptPalantirWindow;
}
extern char g_bfmeFmtD1077[];

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *b, unsigned int n, char *f, ...);
BfmeX1077 *__cdecl bfmeMk1077(BfmeX1077 *a, BfmeX1077 *b);

extern BfmeX1077 *g_bfmeV1077;
extern char g_bfmeFmtM1077[];
extern char g_bfmeFmtN1077[];

void bfmeGo1077A(int a, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];
	BfmeFl1077 *p = ((BfmeR1077 *)g_rva012F19E8WindowManager)->bfmeSlot1077R_11();

	_snprintf(buf1, 0x10, g_bfmeFmtD1077, a);
	_snprintf(buf2, 0x10, "%g", b * p->m_bfme00);
	_snprintf(buf3, 0x10, "%g", c * p->m_bfme04);
	((BfmeR1077 *)g_rva012F19E8WindowManager)->bfmeRun1077(bfmeX1077(), "MoveRadarPing", 3, buf1, buf2, buf3, 0, 0);
}

void bfmeGo1077B(int a, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];
	BfmeFl1077 *p;

	_snprintf(buf1, 0x10, g_bfmeFmtD1077, a);
	p = ((BfmeR1077 *)g_rva012F19E8WindowManager)->bfmeSlot1077R_11();
	_snprintf(buf2, 0x10, "%g", b * p->m_bfme00);
	_snprintf(buf3, 0x10, "%g", c * p->m_bfme04);
	((BfmeR1077 *)g_rva012F19E8WindowManager)->bfmeRun1077(bfmeMk1077(g_bfmeV1077, g_bfmeV1077), g_bfmeFmtM1077, 3,
		buf1, buf2, buf3, 0, 0);
}

void bfmeGo1077C(int a, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];
	BfmeFl1077 *p;

	_snprintf(buf1, 0x10, g_bfmeFmtD1077, a);
	p = ((BfmeR1077 *)g_rva012F19E8WindowManager)->bfmeSlot1077R_11();
	_snprintf(buf2, 0x10, "%g", b * p->m_bfme00);
	_snprintf(buf3, 0x10, "%g", c * p->m_bfme04);
	((BfmeR1077 *)g_rva012F19E8WindowManager)->bfmeRun1077(bfmeMk1077(g_bfmeV1077, g_bfmeV1077), g_bfmeFmtN1077, 3,
		buf1, buf2, buf3, 0, 0);
}
