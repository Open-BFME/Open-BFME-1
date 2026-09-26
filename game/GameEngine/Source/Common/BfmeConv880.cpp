struct BfmeThingENA
{
	void bfmeGoENA(void *a, void *b);
	void bfmeCallENA(void *b);
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

void BfmeThingENA::bfmeGoENA(void *a, void *b)
{
	m_bfmeP = a;
	bfmeCallENA(b);
}

class BfmeSubENC
{
public:
	void bfmeCallENC(void *a);
};

struct BfmeThingENC
{
	BfmeThingENC *bfmeGoENC(void *a);
	BfmeSubENC *m_bfmeP;
};

BfmeThingENC *BfmeThingENC::bfmeGoENC(void *a)
{
	m_bfmeP->bfmeCallENC(a);
	return this;
}

struct BfmeSubENE
{
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
	unsigned char m_bfmePad[0xc];
	int m_bfmeK;
};

struct BfmeThingENE
{
	BfmeSubENE *bfmeGoENE(void *a);
	BfmeSubENE *bfmeBaseENE();
};

BfmeSubENE *BfmeThingENE::bfmeGoENE(void *a)
{
	BfmeSubENE *s = bfmeBaseENE();
	s->m_bfmeP = a;
	s->m_bfmeK = 6;
	return s;
}

extern "C" unsigned char bfmeStrENF[];

class BfmeSubENF
{
public:
	int bfmeCmpENF(const char *s);
};

struct BfmeThingENF
{
	bool bfmeGoENF();
	unsigned char m_bfmeHead[0x14];
	BfmeSubENF m_bfmeSub;
};

bool BfmeThingENF::bfmeGoENF()
{
	return m_bfmeSub.bfmeCmpENF((const char *)bfmeStrENF) == 0;
}

class BfmeGlobENG
{
public:
	void bfmeCallENG();
};

extern BfmeGlobENG *g_bfmeObjENG;

struct BfmeThingENG
{
	void bfmeGoENG(void *unused);
	unsigned char m_bfmeHead[0x30];
	char m_bfmeFlag;
};

void BfmeThingENG::bfmeGoENG(void *unused)
{
	m_bfmeFlag = 1;
	g_bfmeObjENG->bfmeCallENG();
}

struct BfmeHolderENI
{
	void bfmeCallENI(void *x);
};

bool __stdcall bfmeGoENI(void *a)
{
	((BfmeHolderENI *)&a)->bfmeCallENI(a);
	return true;
}

void __cdecl bfmeCallENJ(void *p, void *a);

struct BfmeThingENJ
{
	void bfmeGoENJ(void *a);
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
};

void BfmeThingENJ::bfmeGoENJ(void *a)
{
	bfmeCallENJ(m_bfmeP, a);
}

struct BfmeSubENK
{
	unsigned char m_bfmeHead[0x11];
	char m_bfmeC;
};

class BfmeObjENK
{
public:
	BfmeSubENK *bfmeGetENK();
};

void bfmeGoENK(BfmeObjENK *o, char v)
{
	if (o)
	{
		BfmeSubENK *s = o->bfmeGetENK();
		s->m_bfmeC = v;
	}
}

void *__cdecl bfmeJoinENLa(void *a, void *b);
void *__cdecl bfmeJoinENLb(void *a, void *b);

struct BfmeThingENLa
{
	BfmeThingENLa *bfmeGoENLa(BfmeThingENLa *o);
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

BfmeThingENLa *BfmeThingENLa::bfmeGoENLa(BfmeThingENLa *o)
{
	void *ov = o->m_bfmeP;
	m_bfmeP = bfmeJoinENLa(m_bfmeP, ov);
	return this;
}

struct BfmeThingENLb
{
	BfmeThingENLb *bfmeGoENLb(BfmeThingENLb *o);
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

BfmeThingENLb *BfmeThingENLb::bfmeGoENLb(BfmeThingENLb *o)
{
	void *ov = o->m_bfmeP;
	m_bfmeP = bfmeJoinENLb(m_bfmeP, ov);
	return this;
}

struct BfmeItemENM
{
	virtual void bfmeV0();
	virtual void bfmeVirt1ENM();
	unsigned int m_bfmeFlags;
};

struct BfmeThingENM
{
	void bfmeGoENMa();
	void bfmeGoENMb();
	int m_bfmeN;
	unsigned char m_bfmePad[4];
	BfmeItemENM **m_bfmeArr;
};

void BfmeThingENM::bfmeGoENMa()
{
	BfmeItemENM *it = m_bfmeArr[m_bfmeN - 1];
	unsigned char b = (unsigned char)(it->m_bfmeFlags >> 30);
	if ((b & 1) == 0)
		it->bfmeVirt1ENM();
	--m_bfmeN;
}

void BfmeThingENM::bfmeGoENMb()
{
	BfmeItemENM *it = m_bfmeArr[m_bfmeN - 1];
	unsigned char b = (unsigned char)(it->m_bfmeFlags >> 30);
	if ((b & 1) == 0)
		it->bfmeVirt1ENM();
	--m_bfmeN;
}
