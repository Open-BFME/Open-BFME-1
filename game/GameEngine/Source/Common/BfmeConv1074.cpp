// Open-BFME5 conversions.
// cl: /MD
#include <stdio.h>

class BfmeX1074;

struct BfmeFl1074
{
	float m_bfme00;
	float m_bfme04;
};

class BfmeR1074
{
public:
	virtual void bfmeSlot1074R_0(void);
	virtual void bfmeSlot1074R_1(void);
	virtual void bfmeSlot1074R_2(void);
	virtual void bfmeSlot1074R_3(void);
	virtual void bfmeSlot1074R_4(void);
	virtual void bfmeSlot1074R_5(void);
	virtual void bfmeSlot1074R_6(void);
	virtual void bfmeSlot1074R_7(void);
	virtual void bfmeSlot1074R_8(void);
	virtual void bfmeSlot1074R_9(void);
	virtual void bfmeSlot1074R_10(void);
	virtual BfmeFl1074 * bfmeSlot1074R_11(void);
	void bfmeRun1074(BfmeX1074 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern int g_guiFxWindowHandle;
extern BfmeX1074 *g_bfmeV1074;
extern char g_bfmeFmtD1074[];

BfmeX1074 *__cdecl bfmeMk1074(BfmeX1074 *a, BfmeX1074 *b);

void bfmeGo1074A(float a, float b)
{
	char buf1[0x10];
	char buf2[0x10];
	BfmeFl1074 *p = ((BfmeR1074 *)g_rva012F19E8WindowManager)->bfmeSlot1074R_11();

	_snprintf(buf1, 0x10, "%g", a * p->m_bfme00);
	_snprintf(buf2, 0x10, "%g", b * p->m_bfme04);
	((BfmeR1074 *)g_rva012F19E8WindowManager)->bfmeRun1074(reinterpret_cast<BfmeX1074 *>(g_guiFxWindowHandle), "MoveToolTip", 2, buf1, buf2, 0, 0, 0);
}

void bfmeGo1074B(int a, int b, int c)
{
	char buf1[0x10];
	char buf2[0x10];
	char buf3[0x10];

	_snprintf(buf1, 0x10, g_bfmeFmtD1074, a);
	_snprintf(buf2, 0x10, "%u", b);
	_snprintf(buf3, 0x10, "%u", c);
	((BfmeR1074 *)g_rva012F19E8WindowManager)->bfmeRun1074(bfmeMk1074(g_bfmeV1074, g_bfmeV1074), "CreateRegionPopup", 3,
		buf1, buf2, buf3, 0, 0);
}
