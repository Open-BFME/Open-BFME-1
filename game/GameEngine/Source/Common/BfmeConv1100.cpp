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

// Retail spells this global View *TheTacticalView (0x012F1600); the TU-local
// BfmeD1100 is only the slot view used at the call sites below.
class View;
extern View *TheTacticalView;

void __cdecl bfmeCall1100(int a);

void __stdcall bfmeGo1100A(int a)
{
	BfmeV1100 v;

	bfmeCall1100(a);
	v.m_bfmeX = 1e-4f;
	v.m_bfmeY = 1e-4f;
	((BfmeD1100 *)TheTacticalView)->bfmeSlot1100D_23(&v);
	v.m_bfmeX = -1e-4f;
	v.m_bfmeY = -1e-4f;
	((BfmeD1100 *)TheTacticalView)->bfmeSlot1100D_23(&v);
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
class Mouse;
extern Mouse *TheMouse;

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
	if (reinterpret_cast<BfmeZ1100 *>(TheMouse))
		reinterpret_cast<BfmeZ1100 *>(TheMouse)->bfmeEnd1100(1);
}
