// Open-BFME5 conversions.

class BfmeF1092
{
public:
	virtual void bfmeSlot1092F_0(void);
	virtual void bfmeSlot1092F_1(void);
	virtual void bfmeSlot1092F_2(void);
	virtual void bfmeSlot1092F_3(void);
	virtual void bfmeSlot1092F_4(void);
	virtual void bfmeSlot1092F_5(void);
	virtual void bfmeSlot1092F_6(void);
	virtual void bfmeSlot1092F_7(void);
	virtual void bfmeSlot1092F_8(void);
	virtual void bfmeSlot1092F_9(void);
	virtual void bfmeSlot1092F_10(void);
	virtual void bfmeSlot1092F_11(void);
	virtual void bfmeSlot1092F_12(void);
	virtual void bfmeSlot1092F_13(void);
	virtual void bfmeSlot1092F_14(void);
	virtual void bfmeSlot1092F_15(void);
	virtual void bfmeSlot1092F_16(void);
	virtual void bfmeSlot1092F_17(void);
	virtual void bfmeSlot1092F_18(void);
	virtual void bfmeSlot1092F_19(void);
	virtual void bfmeSlot1092F_20(void);
	virtual void bfmeSlot1092F_21(void);
	virtual void bfmeSlot1092F_22(void);
	virtual void bfmeSlot1092F_23(void);
	virtual void bfmeSlot1092F_24(void);
	virtual void bfmeSlot1092F_25(void);
	virtual void bfmeSlot1092F_26(void);
	virtual void bfmeSlot1092F_27(void);
	virtual void bfmeSlot1092F_28(void);
	virtual void bfmeSlot1092F_29(void);
	virtual void bfmeSlot1092F_30(void);
	virtual void bfmeSlot1092F_31(void);
	virtual void bfmeSlot1092F_32(void);
	virtual void bfmeSlot1092F_33(void);
	virtual void bfmeSlot1092F_34(void);
	virtual void bfmeSlot1092F_35(void);
	virtual void bfmeSlot1092F_36(void);
	virtual void bfmeSlot1092F_37(void);
	virtual void bfmeSlot1092F_38(void);
	virtual void bfmeSlot1092F_39(void);
	virtual void bfmeSlot1092F_40(void);
	virtual void bfmeSlot1092F_41(void);
	virtual void bfmeSlot1092F_42(void);
	virtual void bfmeSlot1092F_43(void);
	virtual void bfmeSlot1092F_44(void);
	virtual void bfmeSlot1092F_45(void);
	virtual void bfmeSlot1092F_46(void);
	virtual void bfmeSlot1092F_47(void);
	virtual void bfmeSlot1092F_48(void);
	virtual void bfmeSlot1092F_49(void);
	virtual void bfmeSlot1092F_50(void);
	virtual void bfmeSlot1092F_51(void);
	virtual void bfmeSlot1092F_52(void);
	virtual void bfmeSlot1092F_53(void);
	virtual void bfmeSlot1092F_54(void);
	virtual void bfmeSlot1092F_55(void);
	virtual void bfmeSlot1092F_56(void);
	virtual void bfmeSlot1092F_57(void);
	virtual void bfmeSlot1092F_58(void);
	virtual void bfmeSlot1092F_59(void);
	virtual void bfmeSlot1092F_60(void);
	virtual void bfmeSlot1092F_61(void);
	virtual void bfmeSlot1092F_62(void);
	virtual void bfmeSlot1092F_63(void);
	virtual void bfmeSlot1092F_64(void);
	virtual void bfmeSlot1092F_65(void);
	virtual void bfmeSlot1092F_66(void);
	virtual void bfmeSlot1092F_67(void);
	virtual void bfmeSlot1092F_68(void);
	virtual void bfmeSlot1092F_69(void);
	virtual void bfmeSlot1092F_70(void);
	virtual void bfmeSlot1092F_71(void);
	virtual void bfmeSlot1092F_72(void);
	virtual void bfmeSlot1092F_73(void);
	virtual void bfmeSlot1092F_74(void);
	virtual void bfmeSlot1092F_75(void);
	virtual int bfmeSlot1092F_76(void);
};

class BfmeR1092
{
public:
	char m_bfmePad[0x24];
	int m_bfme24;
};

class BfmeE1092
{
public:
	char bfmeSkip1092(BfmeR1092 *r);
	int bfmeKind1092(int a);
	char m_bfmePad[0x1a4];
	int m_bfme1a4;
	char m_bfmePad1[0x54];
	BfmeF1092 *m_bfme1fc;
};

class BfmeD1092
{
public:
	BfmeR1092 *bfmeGet1092(int h);
	BfmeR1092 *bfmeLook1092(short *h);
};

class BfmeP1092
{
public:
	virtual void bfmeSlot1092P_0(void);
	virtual void bfmeSlot1092P_1(void);
	virtual void bfmeSlot1092P_2(void);
	virtual void bfmeSlot1092P_3(void);
	virtual void bfmeSlot1092P_4(void);
	virtual void bfmeSlot1092P_5(void);
	virtual void bfmeSlot1092P_6(void);
	virtual void bfmeSlot1092P_7(void);
	virtual void bfmeSlot1092P_8(void);
	virtual void bfmeSlot1092P_9(void);
	virtual void bfmeSlot1092P_10(void);
	virtual void bfmeSlot1092P_11(void);
	virtual void bfmeSlot1092P_12(void);
	virtual void bfmeSlot1092P_13(void);
	virtual void bfmeSlot1092P_14(void);
	virtual void bfmeSlot1092P_15(void);
	virtual void bfmeSlot1092P_16(void);
	virtual void bfmeSlot1092P_17(void);
	virtual void bfmeSlot1092P_18(void);
	virtual void bfmeSlot1092P_19(void);
	virtual void bfmeSlot1092P_20(void);
	virtual void bfmeSlot1092P_21(void);
	virtual void bfmeSlot1092P_22(void);
	virtual void bfmeSlot1092P_23(void);
	virtual void bfmeSlot1092P_24(void);
	virtual void bfmeSlot1092P_25(void);
	virtual BfmeE1092 * bfmeSlot1092P_26(int a);
	int bfmeNext1092(int a);
};

extern BfmeD1092 *g_bfmeD1092;
extern BfmeP1092 *g_bfmeP1092;

char __stdcall bfmeGo1092A(int a, int b)
{
	BfmeE1092 *e = g_bfmeP1092->bfmeSlot1092P_26(b);
	BfmeR1092 *r;
	int h;

	if (!e)
		return 0;
	if (!e->m_bfme1fc)
		return 0;
	h = e->m_bfme1fc->bfmeSlot1092F_76();
	if (!(short)h)
		return 0;
	r = g_bfmeD1092->bfmeGet1092(h);
	if (!r)
		return 0;
	b = g_bfmeP1092->bfmeNext1092(a);
	while ((short)b) {
		if (r == g_bfmeD1092->bfmeLook1092((short *)&b))
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1092B(int a, int b)
{
	BfmeE1092 *e = g_bfmeP1092->bfmeSlot1092P_26(a);

	if (!e)
		return 0;
	if (e->m_bfme1a4 & 8)
		return 0;
	a = g_bfmeP1092->bfmeNext1092(b);
	while ((short)a) {
		BfmeR1092 *r = g_bfmeD1092->bfmeLook1092((short *)&a);

		if (!e->bfmeSkip1092(r)) {
			int m = r->m_bfme24;
			int k = e->bfmeKind1092(m);

			if (k == 1 || k == 2)
				return 1;
		}
	}
	return 0;
}
