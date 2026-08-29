// Open-BFME5 conversions.

struct BfmeM1087
{
	char m_bfmePad[0x54];
	int m_bfme54;
	char m_bfme58;
};

struct BfmeB1087
{
	char m_bfmePad[0x93];
	char m_bfme93;
};

class BfmeN1087
{
public:
	int bfmeConv1087(int a);
	void bfmeSet1087(int a);
};

class BfmeA1087;

extern BfmeM1087 *g_bfmeM1087;
extern BfmeB1087 *g_bfmeB1087;
extern BfmeN1087 *g_bfmeN1087;
extern BfmeA1087 *g_bfmeA1087;

class BfmeQ1087
{
public:
	void bfmeGo1087A(void);
	void bfmeTail1087(void);
	char m_bfmePad[0x17c];
	int m_bfme17c;
};

void BfmeQ1087::bfmeGo1087A(void)
{
	if (g_bfmeM1087->m_bfme58 && g_bfmeB1087->m_bfme93)
		g_bfmeN1087->bfmeSet1087(g_bfmeN1087->bfmeConv1087(m_bfme17c));
	else
		g_bfmeN1087->bfmeSet1087(4);
	if (g_bfmeM1087->m_bfme54 == 8 && g_bfmeA1087)
		bfmeTail1087();
}

class BfmeC1087
{
public:
	int bfmeFind1087(int a);
};

struct BfmeR1087
{
	char m_bfmePad[0x24];
	int m_bfme24;
};

class BfmeD1087
{
public:
	BfmeR1087 *bfmeLook1087(short *h);
};

class BfmeP1087
{
public:
	virtual void bfmeSlot1087P_0(void);
	virtual void bfmeSlot1087P_1(void);
	virtual void bfmeSlot1087P_2(void);
	virtual void bfmeSlot1087P_3(void);
	virtual void bfmeSlot1087P_4(void);
	virtual void bfmeSlot1087P_5(void);
	virtual void bfmeSlot1087P_6(void);
	virtual void bfmeSlot1087P_7(void);
	virtual void bfmeSlot1087P_8(void);
	virtual void bfmeSlot1087P_9(void);
	virtual void bfmeSlot1087P_10(void);
	virtual void bfmeSlot1087P_11(void);
	virtual void bfmeSlot1087P_12(void);
	virtual void bfmeSlot1087P_13(void);
	virtual void bfmeSlot1087P_14(void);
	virtual void bfmeSlot1087P_15(void);
	virtual void bfmeSlot1087P_16(void);
	virtual void bfmeSlot1087P_17(void);
	virtual void bfmeSlot1087P_18(void);
	virtual void bfmeSlot1087P_19(void);
	virtual void bfmeSlot1087P_20(void);
	virtual void bfmeSlot1087P_21(void);
	virtual void bfmeSlot1087P_22(void);
	virtual void bfmeSlot1087P_23(void);
	virtual void bfmeSlot1087P_24(void);
	virtual void bfmeSlot1087P_25(void);
	virtual void bfmeSlot1087P_26(void);
	virtual void bfmeSlot1087P_27(void);
	virtual void bfmeSlot1087P_28(void);
	virtual void bfmeSlot1087P_29(void);
	virtual void bfmeSlot1087P_30(void);
	virtual void bfmeSlot1087P_31(void);
	virtual void bfmeSlot1087P_32(void);
	virtual void bfmeSlot1087P_33(void);
	virtual void bfmeSlot1087P_34(void);
	virtual void bfmeSlot1087P_35(void);
	virtual void bfmeSlot1087P_36(void);
	virtual void bfmeSlot1087P_37(void);
	virtual void bfmeSlot1087P_38(void);
	virtual void bfmeSlot1087P_39(void);
	virtual void bfmeSlot1087P_40(void);
	virtual void bfmeSlot1087P_41(void);
	virtual void bfmeSlot1087P_42(void);
	virtual void bfmeSlot1087P_43(void);
	virtual void bfmeSlot1087P_44(void);
	virtual void bfmeSlot1087P_45(void);
	virtual void bfmeSlot1087P_46(void);
	virtual void bfmeSlot1087P_47(void);
	virtual void bfmeSlot1087P_48(void);
	virtual char bfmeSlot1087P_49(int a, int b, int c);
	int bfmeNext1087(int a);
};

extern BfmeC1087 *g_bfmeC1087;
extern BfmeD1087 *g_bfmeD1087;
extern BfmeP1087 *g_bfmeP1087;

char __stdcall bfmeGo1087B(int a, int b)
{
	int e = g_bfmeC1087->bfmeFind1087(b + 0x10);

	if (e == -1)
		return 0;
	b = g_bfmeP1087->bfmeNext1087(a);
	while ((short)b) {
		BfmeR1087 *r = g_bfmeD1087->bfmeLook1087((short *)&b);

		if (r) {
			int m = r->m_bfme24;

			if (g_bfmeP1087->bfmeSlot1087P_49(m, e, 1))
				return 1;
		}
	}
	return 0;
}
