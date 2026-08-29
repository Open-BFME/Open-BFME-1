// Open-BFME5 conversions.

class BfmeX1079;

class BfmeR1079
{
public:
	void bfmeRun1079(BfmeX1079 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1079 *g_bfmeR1079;
extern char g_bfmeFmt1079[];
extern char g_bfmeLitA1079[];
extern char g_bfmeLitB1079[];

class BfmeM1079
{
public:
	char bfmeChk1079(void);
};

class BfmeL1079
{
public:
	BfmeM1079 *bfmeAt1079(int i);
};

class BfmeP1079
{
public:
	virtual void bfmeSlot1079_0(void);
	virtual void bfmeSlot1079_1(void);
	virtual void bfmeSlot1079_2(void);
	virtual void bfmeSlot1079_3(void);
	virtual void bfmeSlot1079_4(void);
	virtual void bfmeSlot1079_5(void);
	virtual void bfmeSlot1079_6(void);
	virtual void bfmeSlot1079_7(void);
	virtual void bfmeSlot1079_8(void);
	virtual void bfmeSlot1079_9(void);
	virtual void bfmeSlot1079_10(void);
	virtual void bfmeSlot1079_11(void);
	virtual void bfmeSlot1079_12(void);
	virtual void bfmeSlot1079_13(void);
	virtual void bfmeSlot1079_14(void);
	virtual void bfmeSlot1079_15(void);
	virtual void bfmeSlot1079_16(void);
	virtual void bfmeSlot1079_17(void);
	virtual void bfmeSlot1079_18(void);
	virtual void bfmeSlot1079_19(void);
	virtual void bfmeSlot1079_20(void);
	virtual void bfmeSlot1079_21(void);
	virtual void bfmeSlot1079_22(void);
	virtual void bfmeSlot1079_23(void);
	virtual void bfmeSlot1079_24(void);
	virtual void bfmeSlot1079_25(void);
	virtual void bfmeSlot1079_26(void);
	virtual void bfmeSlot1079_27(void);
	virtual void bfmeSlot1079_28(void);
	virtual void bfmeSlot1079_29(void);
	virtual void bfmeSlot1079_30(void);
	virtual void bfmeSlot1079_31(void);
	virtual void bfmeSlot1079_32(void);
	virtual void bfmeSlot1079_33(void);
	virtual void bfmeSlot1079_34(void);
	virtual void bfmeSlot1079_35(void);
	virtual void bfmeSlot1079_36(void);
	virtual void bfmeSlot1079_37(void);
	virtual void bfmeSlot1079_38(void);
	virtual void bfmeSlot1079_39(void);
	virtual void bfmeSlot1079_40(void);
	virtual void bfmeSlot1079_41(void);
	virtual void bfmeSlot1079_42(void);
	virtual void bfmeSlot1079_43(void);
	virtual void bfmeSlot1079_44(void);
	virtual void bfmeSlot1079_45(void);
	virtual void bfmeSlot1079_46(void);
	virtual void bfmeSlot1079_47(void);
	virtual void bfmeSlot1079_48(void);
	virtual BfmeL1079 * bfmeSlot1079_49(void);
};

extern BfmeP1079 *g_bfmeP1079;

class BfmeH1079
{
public:
	void bfmeGo1079A(void);
	char m_bfmePad[0x34];
	BfmeH1079 *m_bfme34;
	char m_bfmePad1[0x19d];
	char m_bfme1d5;
	char m_bfmePad2[0x7a];
	BfmeX1079 *m_bfme250;
};

void BfmeH1079::bfmeGo1079A(void)
{
	BfmeL1079 *l;
	int n;
	int i;
	char v;

	if (!g_bfmeP1079)
		return;
	l = g_bfmeP1079->bfmeSlot1079_49();
	if (!l)
		return;
	n = 0;
	for (i = 0; i < 8; i++) {
		if (l->bfmeAt1079(i)->bfmeChk1079())
			n++;
	}
	v = n >= 2;
	if (m_bfme1d5 == v)
		return;
	m_bfme1d5 = v;
	if (v)
		g_bfmeR1079->bfmeRun1079(m_bfme34->m_bfme250, g_bfmeFmt1079, 1, g_bfmeLitA1079, 0, 0, 0, 0);
	else
		g_bfmeR1079->bfmeRun1079(m_bfme34->m_bfme250, g_bfmeFmt1079, 1, g_bfmeLitB1079, 0, 0, 0, 0);
}
