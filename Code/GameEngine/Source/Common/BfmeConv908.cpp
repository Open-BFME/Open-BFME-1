// Open-BFME5 conversions.

struct BfmeObjRB
{
	int m_bfmeOn;
};

extern BfmeObjRB *g_bfmeGlobRB;
void bfmeOneRB(int f, BfmeObjRB *p);
void bfmeTwoRB(int k, int f);

void bfmeGoRB(void)
{
	BfmeObjRB *p = g_bfmeGlobRB;
	if (p && p->m_bfmeOn) {
		bfmeOneRB(0, p);
		bfmeTwoRB(0xb, 0);
	}
}

void bfmeFreeRC(void *p);

class BfmeThingRC
{
public:
	void bfmeGoRC();
	char m_bfmePad[0x24];
	void *m_bfmeP;
	int m_bfmeN;
};

void BfmeThingRC::bfmeGoRC()
{
	void *p = m_bfmeP;
	if (p) {
		bfmeFreeRC(p);
		m_bfmeP = 0;
		m_bfmeN = 0;
	}
}

class BfmeSubRD
{
public:
	void bfmeFillRD(void **out);
};

class BfmeThingRD
{
public:
	void **bfmeGoRD(void **out);
	char m_bfmePad[0x18];
	BfmeSubRD *m_bfmeSub;
};

void **BfmeThingRD::bfmeGoRD(void **out)
{
	volatile int tmp = 0;
	BfmeSubRD *s = m_bfmeSub;
	if (!s) {
		*out = 0;
		return out;
	}
	s->bfmeFillRD(out);
	return out;
}

class BfmeOtherRE
{
public:
	char bfmeCmpRE(int a, int b);
};

class BfmeThingRE
{
public:
	char bfmeGoRE(BfmeOtherRE *o);
	int m_bfmeA;
	int m_bfmeB;
};

char BfmeThingRE::bfmeGoRE(BfmeOtherRE *o)
{
	if (!o->bfmeCmpRE(m_bfmeA, m_bfmeB))
		return 0;
	++m_bfmeB;
	return 1;
}

void *bfmeOneRF(void *t, void *a);
void *bfmeTwoRF(void *r, void *b);

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *a, void *b);
	char m_bfmePad[0x10];
	void *m_bfmeT;
};

void *BfmeThingRF::bfmeGoRF(void *a, void *b)
{
	void *r = bfmeOneRF(m_bfmeT, a);
	if (!r)
		return b;
	return bfmeTwoRF(r, b);
}

