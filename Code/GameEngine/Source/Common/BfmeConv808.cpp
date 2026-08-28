struct BfmeAEFC
{
	unsigned char m_bfmeHead[0x40];
	float m_bfmeF;
};

struct BfmeBEFC
{
	unsigned char m_bfmeHead[8];
	float m_bfmeF;
};

void __stdcall bfmeCallEFC(BfmeAEFC *a, float v);

void __stdcall bfmeGoEFCa(BfmeAEFC *a, BfmeBEFC *b)
{
	bfmeCallEFC(a, b->m_bfmeF - a->m_bfmeF);
}

struct BfmeBEFD
{
	unsigned char m_bfmeHead[0x40];
	float m_bfmeF;
};

void __stdcall bfmeGoEFCb(BfmeAEFC *a, BfmeBEFD *b)
{
	bfmeCallEFC(a, b->m_bfmeF - a->m_bfmeF);
}

struct BfmeNodeEFE
{
	BfmeNodeEFE *bfmeUpdEFE();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFE *m_bfmeQ;
	unsigned char m_bfmePad[0x18];
	int m_bfmeX;
};

struct BfmeThingEFE
{
	int bfmeGoEFE();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFE *m_bfmeP;
	unsigned char m_bfmePad[0x18];
	int m_bfmeX;
};

int BfmeThingEFE::bfmeGoEFE()
{
	BfmeNodeEFE *p = m_bfmeP;
	if (p)
	{
		BfmeNodeEFE *q = p->m_bfmeQ;
		if (q)
			p = q->bfmeUpdEFE();
		return p->m_bfmeX;
	}
	return m_bfmeX;
}

void *__cdecl bfmeOneEFF(void *a, int n);
void __cdecl bfmeTwoEFF(int n, void *r);

int bfmeGoEFFa(void *a)
{
	bfmeTwoEFF(1, bfmeOneEFF(a, 1));
	return 0;
}

class BfmeThingEFG
{
public:
	BfmeThingEFG *bfmeGoEFGa(BfmeThingEFG *o);
	BfmeThingEFG *bfmeGoEFGb(BfmeThingEFG *o);
	void bfmeClearEFG();
	void bfmeCopyEFG(BfmeThingEFG *o);
};

BfmeThingEFG *BfmeThingEFG::bfmeGoEFGa(BfmeThingEFG *o)
{
	if (o != this)
	{
		bfmeClearEFG();
		bfmeCopyEFG(o);
	}
	return this;
}

BfmeThingEFG *BfmeThingEFG::bfmeGoEFGb(BfmeThingEFG *o)
{
	if (o != this)
	{
		bfmeClearEFG();
		bfmeCopyEFG(o);
	}
	return this;
}

void __cdecl bfmeTwoEFFb(int n, void *r);

int bfmeGoEFFb(void *a)
{
	bfmeTwoEFFb(0, bfmeOneEFF(a, 1));
	return 0;
}

struct BfmeNodeEFH
{
	BfmeNodeEFH *bfmeUpdEFH();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFH *m_bfmeQ;
	unsigned char m_bfmePad[0x10c];
	char m_bfmeC;
};

struct BfmeThingEFH
{
	char bfmeGoEFH();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFH *m_bfmeP;
	unsigned char m_bfmePad[0x10c];
	char m_bfmeC;
};

char BfmeThingEFH::bfmeGoEFH()
{
	BfmeNodeEFH *p = m_bfmeP;
	if (p)
	{
		BfmeNodeEFH *q = p->m_bfmeQ;
		if (q)
			p = q->bfmeUpdEFH();
		return p->m_bfmeC;
	}
	return m_bfmeC;
}
