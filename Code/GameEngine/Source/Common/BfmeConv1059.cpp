// Open-BFME5 conversions.

class BfmeA1059;

class BfmeG1059
{
public:
	void bfmeAdd1059(BfmeA1059 *a, int b);
};

extern BfmeG1059 *g_bfmeG1059;

class BfmeH1059
{
public:
	virtual void bfmeV1059A(void);
	virtual void bfmeV1059B(void);
	virtual void bfmeV1059C(void);
	virtual void bfmeV1059D(void);
	virtual void bfmeV1059E(int a);
};

extern BfmeH1059 *g_bfmeH1059;

class BfmeA1059
{
public:
	void bfmeGo1059A(int a);
	void bfmeUse1059(int a);
};

void BfmeA1059::bfmeGo1059A(int a)
{
	g_bfmeG1059->bfmeAdd1059(this, a);
	bfmeUse1059(a);
	g_bfmeH1059->bfmeV1059E(a);
}

class BfmeS1059
{
public:
	BfmeS1059(void);
	int m_bfme00;
	char m_bfmeBuf[0x1c];
};

class BfmeC1059
{
public:
	virtual void bfmeSlot1059_0(void);
	virtual void bfmeSlot1059_1(void);
	virtual void bfmeSlot1059_2(void);
	virtual void bfmeSlot1059_3(void);
	virtual void bfmeSlot1059_4(void);
	virtual void bfmeSlot1059_5(void);
	virtual void bfmeSlot1059_6(void);
	virtual void bfmeSlot1059_7(void);
	virtual void bfmeSlot1059_8(void);
	virtual void bfmeSlot1059_9(void);
	virtual void bfmeSlot1059_10(void);
	virtual void bfmeSlot1059_11(void);
	virtual void bfmeSlot1059_12(void);
	virtual void bfmeSlot1059_13(void);
	virtual void bfmeSlot1059_14(void);
	virtual void bfmeSlot1059_15(void);
	virtual void bfmeSlot1059_16(void);
	virtual void bfmeSlot1059_17(void);
	virtual void bfmeSlot1059_18(void);
	virtual void bfmeSlot1059_19(void);
	virtual void bfmeSlot1059_20(void);
	virtual void bfmeSlot1059_21(void);
	virtual void bfmeSlot1059_22(void);
	virtual void bfmeSlot1059_23(void);
	virtual void bfmeSlot1059_24(void);
	virtual void bfmeSlot1059_25(void);
	virtual void bfmeSlot1059_26(void);
	virtual void bfmeSlot1059_27(void);
	virtual void bfmeSlot1059_28(void);
	virtual void bfmeSlot1059_29(void);
	virtual void bfmeSlot1059_30(void);
	virtual void bfmeSlot1059_31(void);
	virtual void bfmeSlot1059_32(void);
	virtual void bfmeSlot1059_33(void);
	virtual void bfmeSlot1059_34(void);
	virtual void bfmeSlot1059_35(void);
	virtual void bfmeSlot1059_36(void);
	virtual void bfmeSlot1059_37(void);
	virtual void bfmeSlot1059_38(void);
	virtual void bfmeSlot1059_39(void);
	virtual void bfmeSlot1059_40(void);
	virtual void bfmeSlot1059_41(void);
	virtual void bfmeSlot1059_42(void);
	virtual void bfmeSlot1059_43(void);
	virtual void bfmeSlot1059_44(void);
	virtual void bfmeSlot1059_45(void);
	virtual void bfmeSlot1059_46(void);
	virtual void bfmeSlot1059_47(void);
	virtual void bfmeSlot1059_48(void);
	virtual void bfmeSlot1059_49(char *b, int c, int d, int e);
	virtual void bfmeSlot1059_50(void);
	virtual void bfmeSlot1059_51(void);
	virtual void bfmeSlot1059_52(void);
	virtual void bfmeSlot1059_53(void);
	virtual void bfmeSlot1059_54(void);
	virtual void bfmeSlot1059_55(void);
	virtual void bfmeSlot1059_56(void);
	virtual void bfmeSlot1059_57(void);
	virtual void bfmeSlot1059_58(void);
	virtual void bfmeSlot1059_59(void);
	virtual void bfmeSlot1059_60(void);
	virtual void bfmeSlot1059_61(void);
	virtual void bfmeSlot1059_62(void);
	virtual void bfmeSlot1059_63(void);
	virtual void bfmeSlot1059_64(void);
	virtual void bfmeSlot1059_65(void);
	virtual void bfmeSlot1059_66(void);
	virtual void bfmeSlot1059_67(void);
	virtual void bfmeSlot1059_68(void);
	virtual void bfmeSlot1059_69(void);
	virtual void bfmeSlot1059_70(void);
	virtual void bfmeSlot1059_71(void);
	virtual void bfmeSlot1059_72(void);
	virtual void bfmeSlot1059_73(void);
	virtual void bfmeSlot1059_74(void);
	virtual void bfmeSlot1059_75(void);
	virtual void bfmeSlot1059_76(void);
	virtual void bfmeSlot1059_77(void);
	virtual void bfmeSlot1059_78(void);
	virtual void bfmeSlot1059_79(void);
	virtual void bfmeSlot1059_80(void);
	virtual void bfmeSlot1059_81(void);
	virtual void bfmeSlot1059_82(void);
	virtual void bfmeSlot1059_83(void);
	virtual void bfmeSlot1059_84(void);
	virtual void bfmeSlot1059_85(void);
	virtual void bfmeSlot1059_86(void);
	virtual void bfmeSlot1059_87(void);
	virtual void bfmeSlot1059_88(void);
	virtual void bfmeSlot1059_89(void);
	virtual void bfmeSlot1059_90(void);
	virtual void bfmeSlot1059_91(BfmeS1059 *s);
};

extern BfmeC1059 *g_bfmeC1059;

void bfmeGo1059C(void)
{
	BfmeS1059 s;

	g_bfmeC1059->bfmeSlot1059_91(&s);
	g_bfmeC1059->bfmeSlot1059_49(s.m_bfmeBuf, 1, 0, 0);
}

