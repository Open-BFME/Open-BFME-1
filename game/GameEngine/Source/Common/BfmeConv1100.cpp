// Open-BFME5 conversions.

struct BfmeV1100
{
	float m_bfmeX;
	float m_bfmeY;
};

class BfmeD1100
{
public:
	virtual void bfmeSlot1100D_0(void);
	virtual void bfmeSlot1100D_1(void);
	virtual void bfmeSlot1100D_2(void);
	virtual void bfmeSlot1100D_3(void);
	virtual void bfmeSlot1100D_4(void);
	virtual void bfmeSlot1100D_5(void);
	virtual void bfmeSlot1100D_6(void);
	virtual void bfmeSlot1100D_7(void);
	virtual void bfmeSlot1100D_8(void);
	virtual void bfmeSlot1100D_9(void);
	virtual void bfmeSlot1100D_10(void);
	virtual void bfmeSlot1100D_11(void);
	virtual void bfmeSlot1100D_12(void);
	virtual void bfmeSlot1100D_13(void);
	virtual void bfmeSlot1100D_14(void);
	virtual void bfmeSlot1100D_15(void);
	virtual void bfmeSlot1100D_16(void);
	virtual void bfmeSlot1100D_17(void);
	virtual void bfmeSlot1100D_18(void);
	virtual void bfmeSlot1100D_19(void);
	virtual void bfmeSlot1100D_20(void);
	virtual void bfmeSlot1100D_21(void);
	virtual void bfmeSlot1100D_22(void);
	virtual void bfmeSlot1100D_23(BfmeV1100 *v);
};

extern BfmeD1100 *g_bfmeD1100;

void __cdecl bfmeCall1100(int a);

void __stdcall bfmeGo1100A(int a)
{
	BfmeV1100 v;

	bfmeCall1100(a);
	v.m_bfmeX = 1e-4f;
	v.m_bfmeY = 1e-4f;
	g_bfmeD1100->bfmeSlot1100D_23(&v);
	v.m_bfmeX = -1e-4f;
	v.m_bfmeY = -1e-4f;
	g_bfmeD1100->bfmeSlot1100D_23(&v);
}

struct BfmeA1100
{
	char m_bfmePad[4];
	int m_bfme04;
};

class BfmeB1100
{
public:
	char bfmeChk1100(int a);
};

class BfmeZ1100
{
public:
	void bfmeEnd1100(int a);
};

extern BfmeA1100 *g_bfmeA1100;
extern BfmeB1100 *g_bfmeB1100;
extern BfmeZ1100 *g_bfmeZ1100;

void __cdecl bfmeDo1100(int a);

class BfmeQ1100
{
public:
	void bfmeGo1100B(void);
	char m_bfmePad[0x288];
	char m_bfme288;
};

void BfmeQ1100::bfmeGo1100B(void)
{
	if (g_bfmeA1100->m_bfme04 != 2)
		m_bfme288 = 0;
	if (g_bfmeA1100->m_bfme04 != 1)
		return;
	if (!g_bfmeB1100)
		return;
	if (g_bfmeB1100->bfmeChk1100(8))
		return;
	bfmeDo1100(1);
	if (g_bfmeZ1100)
		g_bfmeZ1100->bfmeEnd1100(1);
}
