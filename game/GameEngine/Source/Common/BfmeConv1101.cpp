// Open-BFME5 conversions.

class BfmeK1101
{
public:
	void bfmeUse1101(int a);
};

class BfmeJ1101
{
public:
	void bfmeDrop1101(int a);
	BfmeK1101 *bfmeFind1101(int a);
};

extern BfmeJ1101 *g_bfmeJ1101;

class BfmeQ1101
{
public:
	virtual void bfmeSlot1101Q_0(void);
	virtual void bfmeSlot1101Q_1(void);
	virtual char bfmeSlot1101Q_2(void);
	void bfmeGo1101A(void);
	char m_bfmePad[0xa0];
	char m_bfmea4;
	char m_bfmePad1[3];
	int m_bfmea8;
};

void BfmeQ1101::bfmeGo1101A(void)
{
	if (!bfmeSlot1101Q_2())
		return;
	m_bfmea4 = 0;
	g_bfmeJ1101->bfmeDrop1101(m_bfmea8);
	{
		BfmeK1101 *k = g_bfmeJ1101->bfmeFind1101(m_bfmea8);

		k->bfmeUse1101(*(int *)((char *)this - 0x2c));
	}
}

class BfmeV1101
{
public:
	virtual void bfmeSlot1101V_0(void);
	virtual void bfmeSlot1101V_1(int a);
};

class BfmeR1101
{
public:
	virtual void bfmeSlot1101R_0(void);
	virtual void bfmeSlot1101R_1(void);
	virtual void bfmeSlot1101R_2(void);
	virtual void bfmeSlot1101R_3(void);
	virtual void bfmeSlot1101R_4(void);
	virtual void bfmeSlot1101R_5(void);
	virtual void bfmeSlot1101R_6(void);
	virtual void bfmeSlot1101R_7(void);
	virtual void bfmeSlot1101R_8(void);
	virtual void bfmeSlot1101R_9(void);
	virtual void bfmeSlot1101R_10(void);
	virtual void bfmeSlot1101R_11(void);
	virtual void bfmeSlot1101R_12(void);
	virtual void bfmeSlot1101R_13(void);
	virtual void bfmeSlot1101R_14(void);
	virtual void bfmeSlot1101R_15(void);
	virtual void bfmeSlot1101R_16(void);
	virtual void bfmeSlot1101R_17(void);
	virtual void bfmeSlot1101R_18(void);
	virtual void bfmeSlot1101R_19(void);
	virtual void bfmeSlot1101R_20(void);
	virtual void bfmeSlot1101R_21(void);
	virtual void bfmeSlot1101R_22(void);
	virtual void bfmeSlot1101R_23(void);
	virtual void bfmeSlot1101R_24(void);
	virtual void bfmeSlot1101R_25(void);
	virtual void bfmeSlot1101R_26(void);
	virtual void bfmeSlot1101R_27(void);
	virtual void bfmeSlot1101R_28(void);
	virtual void bfmeSlot1101R_29(void);
	virtual void bfmeSlot1101R_30(void);
	virtual void bfmeSlot1101R_31(void);
	virtual void bfmeSlot1101R_32(void);
	virtual void bfmeSlot1101R_33(void);
	virtual void bfmeSlot1101R_34(void);
	virtual void bfmeSlot1101R_35(void);
	virtual void bfmeSlot1101R_36(void);
	virtual void bfmeSlot1101R_37(void);
	virtual void bfmeSlot1101R_38(void);
	virtual void bfmeSlot1101R_39(void);
	virtual void bfmeSlot1101R_40(void);
	virtual void bfmeSlot1101R_41(void);
	virtual void bfmeSlot1101R_42(void);
	virtual void bfmeSlot1101R_43(void);
	virtual void bfmeSlot1101R_44(void);
	virtual void bfmeSlot1101R_45(void);
	virtual void bfmeSlot1101R_46(void);
	virtual void bfmeSlot1101R_47(void);
	virtual void bfmeSlot1101R_48(void);
	virtual void bfmeSlot1101R_49(void);
	virtual void bfmeSlot1101R_50(void);
	virtual void bfmeSlot1101R_51(void);
	virtual void bfmeSlot1101R_52(void);
	virtual void bfmeSlot1101R_53(void);
	virtual void bfmeSlot1101R_54(void);
	virtual int bfmeSlot1101R_55(int a, int b);
};

class BfmeC1101
{
public:
	int bfmeConv1101(char *s);
};

extern BfmeC1101 *g_bfmeC1101;
extern BfmeR1101 *g_bfmeR1101;
extern char g_bfmeLit1101[];

class BfmeW1101
{
public:
	char bfmeGo1101B(void);
	char *m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	BfmeV1101 *m_bfme10;
	int m_bfme14;
};

char BfmeW1101::bfmeGo1101B(void)
{
	char *s;
	int v;

	if (m_bfme00)
		s = m_bfme00 + 8;
	else
		s = g_bfmeLit1101;
	int r;

	v = g_bfmeC1101->bfmeConv1101(s);
	m_bfme08 = v;
	r = g_bfmeR1101->bfmeSlot1101R_55(0, v);
	m_bfme14 = m_bfme04;
	m_bfme0c = r;
	m_bfme10->bfmeSlot1101V_1(r);
	return 1;
}
