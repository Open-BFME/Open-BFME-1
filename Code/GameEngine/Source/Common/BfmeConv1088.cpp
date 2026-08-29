// Open-BFME5 conversions.

struct BfmeE1088
{
	char m_bfmePad[0x74];
	int m_bfme74;
};

struct BfmeR1088
{
	char m_bfmePad[0x24];
	int m_bfme24;
};

class BfmeD1088
{
public:
	BfmeR1088 *bfmeLook1088(short *h);
};

class BfmeP1088
{
public:
	virtual void bfmeSlot1088P_0(void);
	virtual void bfmeSlot1088P_1(void);
	virtual void bfmeSlot1088P_2(void);
	virtual void bfmeSlot1088P_3(void);
	virtual void bfmeSlot1088P_4(void);
	virtual void bfmeSlot1088P_5(void);
	virtual void bfmeSlot1088P_6(void);
	virtual void bfmeSlot1088P_7(void);
	virtual void bfmeSlot1088P_8(void);
	virtual void bfmeSlot1088P_9(void);
	virtual void bfmeSlot1088P_10(void);
	virtual void bfmeSlot1088P_11(void);
	virtual void bfmeSlot1088P_12(void);
	virtual void bfmeSlot1088P_13(void);
	virtual void bfmeSlot1088P_14(void);
	virtual void bfmeSlot1088P_15(void);
	virtual void bfmeSlot1088P_16(void);
	virtual void bfmeSlot1088P_17(void);
	virtual void bfmeSlot1088P_18(void);
	virtual void bfmeSlot1088P_19(void);
	virtual void bfmeSlot1088P_20(void);
	virtual void bfmeSlot1088P_21(void);
	virtual void bfmeSlot1088P_22(void);
	virtual void bfmeSlot1088P_23(void);
	virtual void bfmeSlot1088P_24(void);
	virtual void bfmeSlot1088P_25(void);
	virtual BfmeE1088 *bfmeSlot1088P_26(int a);
	virtual void bfmeSlot1088P_27(void);
	virtual void bfmeSlot1088P_28(void);
	virtual void bfmeSlot1088P_29(void);
	virtual void bfmeSlot1088P_30(void);
	virtual void bfmeSlot1088P_31(void);
	virtual void bfmeSlot1088P_32(void);
	virtual void bfmeSlot1088P_33(void);
	virtual void bfmeSlot1088P_34(void);
	virtual void bfmeSlot1088P_35(void);
	virtual void bfmeSlot1088P_36(void);
	virtual void bfmeSlot1088P_37(void);
	virtual void bfmeSlot1088P_38(void);
	virtual void bfmeSlot1088P_39(void);
	virtual void bfmeSlot1088P_40(void);
	virtual void bfmeSlot1088P_41(void);
	virtual void bfmeSlot1088P_42(void);
	virtual void bfmeSlot1088P_43(void);
	virtual void bfmeSlot1088P_44(void);
	virtual char bfmeSlot1088P_45(int a, int b, int c, int d);
	virtual char bfmeSlot1088P_46(int a, int b, int c, int d);
	virtual char bfmeSlot1088P_47(int a, int b, int c, int d);
	virtual char bfmeSlot1088P_48(int a, int b, int c, int d);
	virtual void bfmeSlot1088P_49(void);
	int bfmeNext1088(int a);
};

extern BfmeD1088 *g_bfmeD1088;
extern BfmeP1088 *g_bfmeP1088;

char __stdcall bfmeGo1088_45(int a, int b, int c)
{
	int v = 0;

	if (c) {
		BfmeE1088 *p = g_bfmeP1088->bfmeSlot1088P_26(c);

		if (!p)
			return 0;
		v = p->m_bfme74;
	}
	c = g_bfmeP1088->bfmeNext1088(a);
	while ((short)c) {
		BfmeR1088 *r = g_bfmeD1088->bfmeLook1088((short *)&c);

		if (r) {
			int m = r->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_45(m, b + 0x10, 1, v))
				return 1;
		}
	}
	return 0;
}

char __stdcall bfmeGo1088_46(int a, int b, int c)
{
	int v = 0;

	if (c) {
		BfmeE1088 *p = g_bfmeP1088->bfmeSlot1088P_26(c);

		if (!p)
			return 0;
		v = p->m_bfme74;
	}
	c = g_bfmeP1088->bfmeNext1088(a);
	while ((short)c) {
		BfmeR1088 *r = g_bfmeD1088->bfmeLook1088((short *)&c);

		if (r) {
			int m = r->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_46(m, b + 0x10, 1, v))
				return 1;
		}
	}
	return 0;
}

char __stdcall bfmeGo1088_47(int a, int b, int c)
{
	int v = 0;

	if (c) {
		BfmeE1088 *p = g_bfmeP1088->bfmeSlot1088P_26(c);

		if (!p)
			return 0;
		v = p->m_bfme74;
	}
	c = g_bfmeP1088->bfmeNext1088(a);
	while ((short)c) {
		BfmeR1088 *r = g_bfmeD1088->bfmeLook1088((short *)&c);

		if (r) {
			int m = r->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_47(m, b + 0x10, 1, v))
				return 1;
		}
	}
	return 0;
}

char __stdcall bfmeGo1088_48(int a, int b, int c)
{
	int v = 0;

	if (c) {
		BfmeE1088 *p = g_bfmeP1088->bfmeSlot1088P_26(c);

		if (!p)
			return 0;
		v = p->m_bfme74;
	}
	c = g_bfmeP1088->bfmeNext1088(a);
	while ((short)c) {
		BfmeR1088 *r = g_bfmeD1088->bfmeLook1088((short *)&c);

		if (r) {
			int m = r->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_48(m, b + 0x10, 1, v))
				return 1;
		}
	}
	return 0;
}

