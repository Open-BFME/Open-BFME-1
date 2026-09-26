// Open-BFME5 conversions.

class BfmeX1085;

class BfmeR1085
{
public:
	void bfmeOpen1085(BfmeX1085 *a);
	void bfmeShut1085(BfmeX1085 *a);
};

extern BfmeR1085 *g_bfmeR1085;
extern BfmeX1085 *g_bfmeX1085;
extern char g_bfmeF1085;
extern char g_bfmeG1085;
extern char g_bfmeH1085;

void bfmeGo1085A(void)
{
	if (g_bfmeH1085) {
		g_bfmeR1085->bfmeOpen1085(g_bfmeX1085);
		g_bfmeF1085 = 1;
		g_bfmeH1085 = 0;
	} else if (!g_bfmeF1085) {
		return;
	}
	if (!g_bfmeG1085) {
		g_bfmeR1085->bfmeShut1085(g_bfmeX1085);
		g_bfmeG1085 = 1;
	}
}

class BfmeSub1085
{
public:
	void bfmeSet1085(int a);
};

struct BfmeF1085
{
	char m_bfmePad[0x20];
	BfmeSub1085 m_bfme20;
};

class BfmeE1085
{
public:
	char m_bfmePad[0x204];
	BfmeF1085 *m_bfme204;
};

class BfmeP1085
{
public:
	virtual void bfmeSlot1085_0(void);
	virtual void bfmeSlot1085_1(void);
	virtual void bfmeSlot1085_2(void);
	virtual void bfmeSlot1085_3(void);
	virtual void bfmeSlot1085_4(void);
	virtual void bfmeSlot1085_5(void);
	virtual void bfmeSlot1085_6(void);
	virtual void bfmeSlot1085_7(void);
	virtual void bfmeSlot1085_8(void);
	virtual void bfmeSlot1085_9(void);
	virtual void bfmeSlot1085_10(void);
	virtual void bfmeSlot1085_11(void);
	virtual void bfmeSlot1085_12(void);
	virtual void bfmeSlot1085_13(void);
	virtual void bfmeSlot1085_14(void);
	virtual void bfmeSlot1085_15(void);
	virtual void bfmeSlot1085_16(void);
	virtual void bfmeSlot1085_17(void);
	virtual void bfmeSlot1085_18(void);
	virtual void bfmeSlot1085_19(void);
	virtual void bfmeSlot1085_20(void);
	virtual void bfmeSlot1085_21(void);
	virtual void bfmeSlot1085_22(void);
	virtual void bfmeSlot1085_23(void);
	virtual void bfmeSlot1085_24(void);
	virtual void bfmeSlot1085_25(void);
	virtual BfmeE1085 * bfmeSlot1085_26(int a);
	void bfmeUse1085(BfmeE1085 *a, int b);
};

extern BfmeP1085 *g_bfmeP1085;

void __stdcall bfmeGo1085B(int a, int b, char c)
{
	BfmeE1085 *e = g_bfmeP1085->bfmeSlot1085_26(a);

	if (!e)
		return;
	if (!e->m_bfme204)
		return;
	e->m_bfme204->m_bfme20.bfmeSet1085(1);
	if (c)
		g_bfmeP1085->bfmeUse1085(e, b * 5);
	else
		g_bfmeP1085->bfmeUse1085(e, b);
}
