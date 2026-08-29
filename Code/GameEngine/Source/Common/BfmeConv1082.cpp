// Open-BFME5 conversions.

class BfmeA1082
{
public:
	virtual void bfmeSlot1082A_0(void);
	virtual void bfmeSlot1082A_1(void);
	virtual void bfmeSlot1082A_2(void);
	virtual void bfmeSlot1082A_3(void);
	virtual void bfmeSlot1082A_4(void);
	virtual void bfmeSlot1082A_5(void);
	virtual void bfmeSlot1082A_6(void);
	virtual void bfmeSlot1082A_7(void);
	virtual void bfmeSlot1082A_8(void);
	virtual void bfmeSlot1082A_9(void);
	virtual void bfmeSlot1082A_10(void);
	virtual void bfmeSlot1082A_11(void);
	virtual void bfmeSlot1082A_12(void);
	virtual void bfmeSlot1082A_13(void);
	virtual void bfmeSlot1082A_14(void);
	virtual void bfmeSlot1082A_15(void);
	virtual void bfmeSlot1082A_16(void);
	virtual void bfmeSlot1082A_17(void);
	virtual void bfmeSlot1082A_18(void);
	virtual void bfmeSlot1082A_19(int a);
};

extern BfmeA1082 *g_bfmeA1082;

struct BfmeB1082
{
	char m_bfmePad[0x74];
	char m_bfme74;
};

extern BfmeB1082 *g_bfmeB1082;

class BfmeC1082
{
public:
	virtual void bfmeSlot1082C_0(void);
	virtual void bfmeSlot1082C_1(void);
	virtual void bfmeSlot1082C_2(void);
	virtual void bfmeSlot1082C_3(void);
	virtual void bfmeSlot1082C_4(void);
	virtual void bfmeSlot1082C_5(void);
	virtual void bfmeSlot1082C_6(void);
	virtual void bfmeSlot1082C_7(void);
	virtual void bfmeSlot1082C_8(void);
	virtual void bfmeSlot1082C_9(void);
	virtual void bfmeSlot1082C_10(void);
	virtual void bfmeSlot1082C_11(void);
	virtual void bfmeSlot1082C_12(void);
	virtual void bfmeSlot1082C_13(void);
	virtual void bfmeSlot1082C_14(void);
	virtual void bfmeSlot1082C_15(void);
	virtual void bfmeSlot1082C_16(void);
	virtual void bfmeSlot1082C_17(void);
	virtual void bfmeSlot1082C_18(void);
	virtual void bfmeSlot1082C_19(void);
	virtual void bfmeSlot1082C_20(void);
	virtual void bfmeSlot1082C_21(void);
	virtual void bfmeSlot1082C_22(void);
	virtual void bfmeSlot1082C_23(void);
	virtual void bfmeSlot1082C_24(void);
	virtual void bfmeSlot1082C_25(void);
	virtual void bfmeSlot1082C_26(void);
	virtual void bfmeSlot1082C_27(void);
	virtual void bfmeSlot1082C_28(void);
	virtual void bfmeSlot1082C_29(void);
	virtual void bfmeSlot1082C_30(void);
	virtual void bfmeSlot1082C_31(void);
	virtual void bfmeSlot1082C_32(void);
	virtual void bfmeSlot1082C_33(void);
	virtual void bfmeSlot1082C_34(void);
	virtual void bfmeSlot1082C_35(void);
	virtual void bfmeSlot1082C_36(void);
	virtual void bfmeSlot1082C_37(void);
	virtual void bfmeSlot1082C_38(void);
	virtual void bfmeSlot1082C_39(void);
	virtual void bfmeSlot1082C_40(void);
	virtual void bfmeSlot1082C_41(void);
	virtual void bfmeSlot1082C_42(void);
	virtual void bfmeSlot1082C_43(void);
	virtual void bfmeSlot1082C_44(void);
	virtual void bfmeSlot1082C_45(void);
	virtual void bfmeSlot1082C_46(void);
	virtual void bfmeSlot1082C_47(void);
	virtual void bfmeSlot1082C_48(void);
	virtual void bfmeSlot1082C_49(void);
	virtual void bfmeSlot1082C_50(void);
	virtual void bfmeSlot1082C_51(void);
	virtual void bfmeSlot1082C_52(void);
	virtual void bfmeSlot1082C_53(void);
	virtual void bfmeSlot1082C_54(void);
	virtual void bfmeSlot1082C_55(void);
	virtual void bfmeSlot1082C_56(void);
	virtual void bfmeSlot1082C_57(void);
	virtual void bfmeSlot1082C_58(void);
	virtual void bfmeSlot1082C_59(void);
	void bfmeStop1082(void);
};

extern BfmeC1082 *g_bfmeC1082;

class BfmeQ1082
{
public:
	void bfmeGo1082A(void);
	char m_bfmePad[8];
	int m_bfme08;
	char m_bfmePad1[0x10];
	int m_bfme1c;
	int m_bfme20;
};

void BfmeQ1082::bfmeGo1082A(void)
{
	if (m_bfme1c != 1) {
		g_bfmeA1082->bfmeSlot1082A_19(m_bfme1c);
		m_bfme1c = 1;
	}
	if (m_bfme20 != 1) {
		g_bfmeA1082->bfmeSlot1082A_19(m_bfme20);
		m_bfme20 = 1;
	}
	g_bfmeB1082->m_bfme74 = 0;
	g_bfmeC1082->bfmeSlot1082C_59();
	g_bfmeC1082->bfmeStop1082();
	m_bfme08 = 0;
}

class BfmeS1082
{
public:
	virtual void bfmeSlot1082S_0(void);
	virtual void bfmeSlot1082S_1(void);
};

extern BfmeS1082 *g_bfmeS1082_0;
extern BfmeS1082 *g_bfmeS1082_1;
extern BfmeS1082 *g_bfmeS1082_2;
extern BfmeS1082 *g_bfmeS1082_3;
extern BfmeS1082 *g_bfmeS1082_4;
extern BfmeS1082 *g_bfmeS1082_5;
extern BfmeS1082 *g_bfmeS1082_6;
extern BfmeS1082 *g_bfmeS1082_7;

void bfmeGo1082B(void)
{
	if (g_bfmeS1082_0) {
		g_bfmeS1082_0->bfmeSlot1082S_1();
		g_bfmeS1082_0 = 0;
	}
	if (g_bfmeS1082_1) {
		g_bfmeS1082_1->bfmeSlot1082S_1();
		g_bfmeS1082_1 = 0;
	}
	if (g_bfmeS1082_2) {
		g_bfmeS1082_2->bfmeSlot1082S_1();
		g_bfmeS1082_2 = 0;
	}
	if (g_bfmeS1082_3) {
		g_bfmeS1082_3->bfmeSlot1082S_1();
		g_bfmeS1082_3 = 0;
	}
}

void bfmeGo1082C(void)
{
	if (g_bfmeS1082_4) {
		g_bfmeS1082_4->bfmeSlot1082S_1();
		g_bfmeS1082_4 = 0;
	}
	if (g_bfmeS1082_5) {
		g_bfmeS1082_5->bfmeSlot1082S_1();
		g_bfmeS1082_5 = 0;
	}
	if (g_bfmeS1082_6) {
		g_bfmeS1082_6->bfmeSlot1082S_1();
		g_bfmeS1082_6 = 0;
	}
	if (g_bfmeS1082_7) {
		g_bfmeS1082_7->bfmeSlot1082S_1();
		g_bfmeS1082_7 = 0;
	}
}
