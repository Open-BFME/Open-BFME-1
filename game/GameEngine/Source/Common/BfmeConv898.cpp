// Open-BFME5 conversions.

struct BfmeSubGE
{
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

class BfmeThingGE
{
public:
	void bfmeGoGE(BfmeSubGE *d);
	void bfmeOneGE(BfmeSubGE *d, int *x, int *y);
	void bfmeTwoGE(BfmeSubGE *d, int *x, int *y);
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void BfmeThingGE::bfmeGoGE(BfmeSubGE *d)
{
	bfmeOneGE(d, &d->m_bfmeB, &m_bfmeB);
	bfmeTwoGE(d, &d->m_bfmeC, &m_bfmeC);
}

class BfmeResGH
{
public:
	void bfmeOneGH(void *a, void *b);
	void bfmeTwoGH(void *a, void *b);
};

class BfmeThingGH
{
public:
	void bfmeGoGH(void *a, void *b);
	char m_bfmePad[0x58];
	BfmeResGH *m_bfmeOne;
	BfmeResGH *m_bfmeTwo;
};

void BfmeThingGH::bfmeGoGH(void *a, void *b)
{
	if (m_bfmeOne)
		m_bfmeOne->bfmeOneGH(a, b);
	if (m_bfmeTwo)
		m_bfmeTwo->bfmeTwoGH(a, b);
}

class BfmeSubGI
{
public:
	void bfmeUseGI(void *b);
};

class BfmeObjGI
{
public:
	virtual void bfmeSlotGI00();
	virtual void bfmeSlotGI01();
	virtual void bfmeSlotGI02();
	virtual void bfmeSlotGI03();
	virtual void bfmeSlotGI04();
	virtual void bfmeSlotGI05();
	virtual void bfmeSlotGI06();
	virtual void bfmeSlotGI07();
	virtual void bfmeSlotGI08();
	virtual void bfmeSlotGI09();
	virtual BfmeSubGI *bfmeGetGI();
};

class BfmeGlobGI
{
public:
	virtual void bfmeSlotGJ00();
	virtual void bfmeSlotGJ01();
	virtual void bfmeSlotGJ02();
	virtual void bfmeSlotGJ03();
	virtual void bfmeSlotGJ04();
	virtual void bfmeSlotGJ05();
	virtual void bfmeSlotGJ06();
	virtual void bfmeSlotGJ07();
	virtual void bfmeSlotGJ08();
	virtual void bfmeSlotGJ09();
	virtual void bfmeSlotGJ10();
	virtual void bfmeSlotGJ11();
	virtual void bfmeSlotGJ12();
	virtual void bfmeSlotGJ13();
	virtual void bfmeSlotGJ14();
	virtual void bfmeSlotGJ15();
	virtual void bfmeSlotGJ16();
	virtual void bfmeSlotGJ17();
	virtual void bfmeSlotGJ18();
	virtual void bfmeSlotGJ19();
	virtual void bfmeSlotGJ20();
	virtual void bfmeSlotGJ21();
	virtual void bfmeSlotGJ22();
	virtual void bfmeSlotGJ23();
	virtual void bfmeSlotGJ24();
	virtual void bfmeSlotGJ25();
	virtual BfmeObjGI *bfmeFindGI(void *a);
};

extern BfmeGlobGI *g_bfmeGlobGI;

void __stdcall bfmeGoGI(void *a, void *b)
{
	BfmeObjGI *o = g_bfmeGlobGI->bfmeFindGI(a);
	if (o) {
		BfmeSubGI *s = o->bfmeGetGI();
		if (s)
			s->bfmeUseGI(b);
	}
}
