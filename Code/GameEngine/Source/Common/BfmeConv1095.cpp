// Open-BFME5 conversions.

struct BfmeZ1095B
{
	char m_bfmePad[4];
	int m_bfme04;
};

class BfmeR1095
{
public:
	void bfmeAdd1095(BfmeZ1095B *z, int k);
};

class BfmeD1095A
{
public:
	BfmeR1095 *bfmeLook1095(short *h);
};

class BfmeP1095
{
public:
	int bfmeFirst1095(int a, int b);
};

class BfmeQ1095A
{
public:
	BfmeZ1095B *bfmeGet1095(int a);
};

extern BfmeD1095A *g_bfmeD1095;
extern BfmeP1095 *g_bfmeP1095;
extern BfmeQ1095A *g_bfmeQ1095;

void __stdcall bfmeGo1095A(int a, int b)
{
	a = g_bfmeP1095->bfmeFirst1095(a, 0);
	while ((short)a) {
		BfmeR1095 *r = g_bfmeD1095->bfmeLook1095((short *)&a);

		if (r) {
			BfmeZ1095B *z = g_bfmeQ1095->bfmeGet1095(b);

			if (!z->m_bfme04)
				r->bfmeAdd1095(z, 2);
		}
	}
}

class BfmeA1095
{
public:
	virtual void bfmeSlot1095A_0(void);
	virtual void bfmeSlot1095A_1(void);
	virtual void bfmeSlot1095A_2(void);
	virtual void bfmeSlot1095A_3(void);
	virtual void bfmeSlot1095A_4(void);
	virtual void bfmeSlot1095A_5(void);
	virtual void bfmeSlot1095A_6(void);
	virtual void bfmeSlot1095A_7(void);
	virtual void bfmeSlot1095A_8(void);
	virtual void bfmeSlot1095A_9(void);
	virtual void bfmeSlot1095A_10(void);
	virtual void bfmeSlot1095A_11(void);
	virtual void bfmeSlot1095A_12(void);
	virtual void bfmeSlot1095A_13(void);
	virtual void bfmeSlot1095A_14(void);
	virtual void bfmeSlot1095A_15(void);
	virtual void bfmeSlot1095A_16(void);
	virtual void bfmeSlot1095A_17(void);
	virtual void bfmeSlot1095A_18(void);
	virtual void bfmeSlot1095A_19(void);
	virtual void bfmeSlot1095A_20(void);
	virtual void bfmeSlot1095A_21(void);
	virtual void bfmeSlot1095A_22(void);
	virtual void bfmeSlot1095A_23(void);
	virtual void bfmeSlot1095A_24(void);
	virtual void bfmeSlot1095A_25(void);
	virtual void bfmeSlot1095A_26(void);
	virtual void bfmeSlot1095A_27(void);
	virtual void bfmeSlot1095A_28(void);
	virtual void bfmeSlot1095A_29(void);
	virtual void bfmeSlot1095A_30(void);
	virtual void bfmeSlot1095A_31(void);
	virtual void bfmeSlot1095A_32(void);
	virtual void bfmeSlot1095A_33(void);
	virtual void bfmeSlot1095A_34(void);
	virtual void bfmeSlot1095A_35(void);
	virtual void bfmeSlot1095A_36(void);
	virtual void bfmeSlot1095A_37(void);
	virtual void bfmeSlot1095A_38(void);
	virtual void bfmeSlot1095A_39(void);
	virtual void bfmeSlot1095A_40(int a);
};

class BfmeE1095
{
public:
	virtual void bfmeSlot1095E_0(void);
	virtual void bfmeSlot1095E_1(void);
	virtual void bfmeSlot1095E_2(void);
	virtual void bfmeSlot1095E_3(void);
	virtual void bfmeSlot1095E_4(void);
	virtual void bfmeSlot1095E_5(void);
	virtual void bfmeSlot1095E_6(void);
	virtual void bfmeSlot1095E_7(void);
	virtual void bfmeSlot1095E_8(void);
	virtual void bfmeSlot1095E_9(void);
	virtual void bfmeSlot1095E_10(void);
	virtual void bfmeSlot1095E_11(void);
	virtual void bfmeSlot1095E_12(void);
	virtual void bfmeSlot1095E_13(void);
	virtual void bfmeSlot1095E_14(void);
	virtual void bfmeSlot1095E_15(void);
	virtual void bfmeSlot1095E_16(void);
	virtual void bfmeSlot1095E_17(void);
	virtual void bfmeSlot1095E_18(void);
	virtual void bfmeSlot1095E_19(void);
	virtual void bfmeSlot1095E_20(void);
	virtual void bfmeSlot1095E_21(void);
	virtual void bfmeSlot1095E_22(void);
	virtual void bfmeSlot1095E_23(void);
	virtual void bfmeSlot1095E_24(void);
	virtual void bfmeSlot1095E_25(void);
	virtual void bfmeSlot1095E_26(void);
	virtual void bfmeSlot1095E_27(void);
	virtual void bfmeSlot1095E_28(void);
	virtual void bfmeSlot1095E_29(void);
	virtual void bfmeSlot1095E_30(void);
	virtual void bfmeSlot1095E_31(void);
	virtual void bfmeSlot1095E_32(void);
	virtual void bfmeSlot1095E_33(void);
	virtual void bfmeSlot1095E_34(void);
	virtual void bfmeSlot1095E_35(void);
	virtual void bfmeSlot1095E_36(void);
	virtual void bfmeSlot1095E_37(void);
	virtual void bfmeSlot1095E_38(void);
	virtual void bfmeSlot1095E_39(void);
	virtual void bfmeSlot1095E_40(void);
	virtual void bfmeSlot1095E_41(void);
	virtual void bfmeSlot1095E_42(void);
	virtual void bfmeSlot1095E_43(void);
	virtual void bfmeSlot1095E_44(void);
	virtual void bfmeSlot1095E_45(void);
	virtual void bfmeSlot1095E_46(void);
	virtual void bfmeSlot1095E_47(void);
	virtual void bfmeSlot1095E_48(void);
	virtual void bfmeSlot1095E_49(void);
	virtual void bfmeSlot1095E_50(void);
	virtual void bfmeSlot1095E_51(void);
	virtual void bfmeSlot1095E_52(void);
	virtual void bfmeSlot1095E_53(void);
	virtual void bfmeSlot1095E_54(void);
	virtual void bfmeSlot1095E_55(void);
	virtual void bfmeSlot1095E_56(void);
	virtual void bfmeSlot1095E_57(void);
	virtual void bfmeSlot1095E_58(void);
	virtual void bfmeSlot1095E_59(void);
	virtual void bfmeSlot1095E_60(void);
	virtual void bfmeSlot1095E_61(void);
	virtual void bfmeSlot1095E_62(void);
	virtual void bfmeSlot1095E_63(void);
	virtual void bfmeSlot1095E_64(void);
	virtual void bfmeSlot1095E_65(void);
	virtual void bfmeSlot1095E_66(void);
	virtual void bfmeSlot1095E_67(void);
	virtual void bfmeSlot1095E_68(void);
	virtual void bfmeSlot1095E_69(void);
	virtual void bfmeSlot1095E_70(void);
	virtual void bfmeSlot1095E_71(void);
	virtual void bfmeSlot1095E_72(void);
	virtual void bfmeSlot1095E_73(void);
	virtual void bfmeSlot1095E_74(void);
	virtual void bfmeSlot1095E_75(void);
	virtual void bfmeSlot1095E_76(void);
	virtual void bfmeSlot1095E_77(void);
	virtual void bfmeSlot1095E_78(void);
	virtual void bfmeSlot1095E_79(void);
	virtual void bfmeSlot1095E_80(void);
	virtual void bfmeSlot1095E_81(void);
	virtual void bfmeSlot1095E_82(void);
	virtual void bfmeSlot1095E_83(void);
	virtual void bfmeSlot1095E_84(void);
	virtual void bfmeSlot1095E_85(void);
	virtual void bfmeSlot1095E_86(void);
	virtual void bfmeSlot1095E_87(void);
	virtual void bfmeSlot1095E_88(void);
	virtual void bfmeSlot1095E_89(void);
	virtual void bfmeSlot1095E_90(void);
	virtual void bfmeSlot1095E_91(void);
	virtual void bfmeSlot1095E_92(void);
	virtual void bfmeSlot1095E_93(void);
	virtual void bfmeSlot1095E_94(void);
	virtual void bfmeSlot1095E_95(void);
	virtual void bfmeSlot1095E_96(void);
	virtual void bfmeSlot1095E_97(void);
	virtual void bfmeSlot1095E_98(void);
	virtual void bfmeSlot1095E_99(void);
	virtual void bfmeSlot1095E_100(void);
	virtual void bfmeSlot1095E_101(void);
	virtual void bfmeSlot1095E_102(void);
	virtual void bfmeSlot1095E_103(void);
	virtual void bfmeSlot1095E_104(int a);
};

class BfmeZ1095
{
public:
	virtual void bfmeSlot1095Z_0(void);
	virtual void bfmeSlot1095Z_1(void);
	virtual void bfmeSlot1095Z_2(void);
	virtual void bfmeSlot1095Z_3(void);
	virtual void bfmeSlot1095Z_4(void);
	virtual void bfmeSlot1095Z_5(void);
	virtual void bfmeSlot1095Z_6(void);
	virtual void bfmeSlot1095Z_7(void);
	virtual void bfmeSlot1095Z_8(void);
	virtual void bfmeSlot1095Z_9(void);
	virtual void bfmeSlot1095Z_10(void);
	virtual void bfmeSlot1095Z_11(void);
	virtual void bfmeSlot1095Z_12(void);
	virtual void bfmeSlot1095Z_13(void);
	virtual void bfmeSlot1095Z_14(int a);
};

class BfmeT1095
{
public:
	void bfmeTail1095(void);
};

extern BfmeA1095 *g_bfmeA1095;
extern BfmeE1095 *g_bfmeE1095;
extern BfmeZ1095 *g_bfmeZ1095;
extern BfmeT1095 *g_bfmeT1095;
extern int g_bfmeV1095;

class BfmeW1095
{
public:
	void bfmeGo1095B(void);
	char m_bfmePad[0x1c];
	char m_bfme1c;
	char m_bfmePad1[0x1b];
	char m_bfme38;
	char m_bfme39;
	char m_bfmePad2[0x10e];
	int m_bfme148;
};

void BfmeW1095::bfmeGo1095B(void)
{
	m_bfme38 = 0;
	m_bfme1c = 0;
	g_bfmeA1095->bfmeSlot1095A_40(0);
	if (!m_bfme39)
		g_bfmeE1095->bfmeSlot1095E_104(0);
	g_bfmeZ1095->bfmeSlot1095Z_14(g_bfmeV1095);
	m_bfme148 = 0;
	if (g_bfmeT1095)
		g_bfmeT1095->bfmeTail1095();
}
