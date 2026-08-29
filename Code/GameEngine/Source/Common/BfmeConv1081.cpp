// Open-BFME5 conversions.

struct BfmeG1081
{
	char m_bfmePad[0x24];
	char m_bfme24;
};

class BfmeE1081
{
public:
	char m_bfmePad[0x38];
	char m_bfme38;
	char m_bfmePad1[0x1d7];
	BfmeG1081 *m_bfme210;
};

class BfmeP1081
{
public:
	virtual void bfmeSlot1081_0(void);
	virtual void bfmeSlot1081_1(void);
	virtual void bfmeSlot1081_2(void);
	virtual void bfmeSlot1081_3(void);
	virtual void bfmeSlot1081_4(void);
	virtual void bfmeSlot1081_5(void);
	virtual void bfmeSlot1081_6(void);
	virtual void bfmeSlot1081_7(void);
	virtual void bfmeSlot1081_8(void);
	virtual void bfmeSlot1081_9(void);
	virtual void bfmeSlot1081_10(void);
	virtual void bfmeSlot1081_11(void);
	virtual void bfmeSlot1081_12(void);
	virtual void bfmeSlot1081_13(void);
	virtual void bfmeSlot1081_14(void);
	virtual void bfmeSlot1081_15(void);
	virtual void bfmeSlot1081_16(void);
	virtual void bfmeSlot1081_17(void);
	virtual void bfmeSlot1081_18(void);
	virtual void bfmeSlot1081_19(void);
	virtual void bfmeSlot1081_20(void);
	virtual void bfmeSlot1081_21(void);
	virtual void bfmeSlot1081_22(void);
	virtual void bfmeSlot1081_23(void);
	virtual void bfmeSlot1081_24(void);
	virtual void bfmeSlot1081_25(void);
	virtual BfmeE1081 * bfmeSlot1081_26(int a);
};

extern BfmeP1081 *g_bfmeP1081;

class BfmeF1081;

class BfmeJ1081
{
public:
	BfmeF1081 *bfmeFind1081(int a);
	void bfmeAdd1081(BfmeF1081 *a, BfmeE1081 *b, int c, int d);
};

extern BfmeJ1081 *g_bfmeJ1081;

void __stdcall bfmeGo1081A(int a, int b)
{
	BfmeE1081 *e = g_bfmeP1081->bfmeSlot1081_26(a);
	BfmeF1081 *f;

	if (!e)
		return;
	f = g_bfmeJ1081->bfmeFind1081(b);
	if (!f)
		return;
	g_bfmeJ1081->bfmeAdd1081(f, e, 0, 1);
	e->m_bfme210->m_bfme24 = 0;
}

class BfmeD1081
{
public:
	char bfmeDo1081(BfmeE1081 *a, char *b, char *c, int d);
};

struct BfmeQ1081
{
	char m_bfmePad[0xc];
	BfmeD1081 *m_bfme0c;
};

extern BfmeQ1081 *g_bfmeQ1081;

char __stdcall bfmeGo1081B(int a, int b)
{
	BfmeE1081 *e = g_bfmeP1081->bfmeSlot1081_26(a);
	BfmeE1081 *f;

	if (!e)
		return 0;
	f = g_bfmeP1081->bfmeSlot1081_26(b);
	if (!f)
		return 0;
	{
		BfmeD1081 *d = g_bfmeQ1081->m_bfme0c;

		return d->bfmeDo1081(e, &e->m_bfme38, &f->m_bfme38, 0);
	}
}
