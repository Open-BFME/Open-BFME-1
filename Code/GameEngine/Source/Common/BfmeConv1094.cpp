// Open-BFME5 conversions.

class BfmeR1094;

struct BfmeW1094
{
	char m_bfmePad[8];
	int m_bfme08;
};

class BfmeF1094
{
public:
	virtual void bfmeSlot1094F_0(void);
	virtual void bfmeSlot1094F_1(void);
	virtual void bfmeSlot1094F_2(void);
	virtual void bfmeSlot1094F_3(void);
	virtual void bfmeSlot1094F_4(void);
	virtual void bfmeSlot1094F_5(void);
	virtual void bfmeSlot1094F_6(void);
	virtual void bfmeSlot1094F_7(void);
	virtual void bfmeSlot1094F_8(void);
	virtual void bfmeSlot1094F_9(void);
	virtual void bfmeSlot1094F_10(void);
	virtual void bfmeSlot1094F_11(void);
	virtual void bfmeSlot1094F_12(void);
	virtual void bfmeSlot1094F_13(void);
	virtual void bfmeSlot1094F_14(void);
	virtual BfmeW1094 * bfmeSlot1094F_15(void);
};

struct BfmeE1094
{
	char m_bfmePad[0x200];
	BfmeF1094 *m_bfme200;
};

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094(void);
};

class BfmeB1094
{
public:
	BfmeK1094 *bfmeFind1094(int a);
};

class BfmeD1094
{
public:
	BfmeR1094 *bfmeLook1094(short *h);
};

class BfmeP1094
{
public:
	virtual void bfmeSlot1094P_0(void);
	virtual void bfmeSlot1094P_1(void);
	virtual void bfmeSlot1094P_2(void);
	virtual void bfmeSlot1094P_3(void);
	virtual void bfmeSlot1094P_4(void);
	virtual void bfmeSlot1094P_5(void);
	virtual void bfmeSlot1094P_6(void);
	virtual void bfmeSlot1094P_7(void);
	virtual void bfmeSlot1094P_8(void);
	virtual void bfmeSlot1094P_9(void);
	virtual void bfmeSlot1094P_10(void);
	virtual void bfmeSlot1094P_11(void);
	virtual void bfmeSlot1094P_12(void);
	virtual void bfmeSlot1094P_13(void);
	virtual void bfmeSlot1094P_14(void);
	virtual void bfmeSlot1094P_15(void);
	virtual void bfmeSlot1094P_16(void);
	virtual void bfmeSlot1094P_17(void);
	virtual void bfmeSlot1094P_18(void);
	virtual void bfmeSlot1094P_19(void);
	virtual void bfmeSlot1094P_20(void);
	virtual void bfmeSlot1094P_21(void);
	virtual void bfmeSlot1094P_22(void);
	virtual void bfmeSlot1094P_23(void);
	virtual void bfmeSlot1094P_24(void);
	virtual void bfmeSlot1094P_25(void);
	virtual BfmeE1094 * bfmeSlot1094P_26(int a);
	int bfmeNext1094(int a);
};

extern BfmeB1094 *g_bfmeB1094;
extern BfmeD1094 *g_bfmeD1094;
extern BfmeP1094 *g_bfmeP1094;

char __stdcall bfmeGo1094A(int a, int b)
{
	BfmeE1094 *e = g_bfmeP1094->bfmeSlot1094P_26(a);
	BfmeW1094 *w;
	BfmeK1094 *k;

	if (!e)
		return 0;
	if (!e->m_bfme200)
		return 0;
	w = e->m_bfme200->bfmeSlot1094F_15();
	if (!w)
		return 0;
	k = g_bfmeB1094->bfmeFind1094(w->m_bfme08);
	if (!k)
		return 0;
	a = g_bfmeP1094->bfmeNext1094(b);
	while ((short)a) {
		BfmeR1094 *r = g_bfmeD1094->bfmeLook1094((short *)&a);

		if (k->bfmeCur1094() == r)
			return 1;
	}
	return 0;
}
