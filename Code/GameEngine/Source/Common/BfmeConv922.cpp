// Open-BFME5 conversions.

struct BfmeState922A
{
	char m_bfmePad[0x10c];
	int m_bfmeMode;
};

class BfmeTail922A
{
public:
	char bfmeTail922A();
};

extern BfmeState922A *g_bfme922State;
extern BfmeTail922A *g_bfme922Tail;

char bfmeGo922A(void)
{
	if (g_bfme922State->m_bfmeMode != 6)
		return 0;
	return g_bfme922Tail->bfmeTail922A();
}

class BfmeGlob922D
{
public:
	virtual void bfmeSlot922D00();
	virtual void bfmeSlot922D01();
	virtual void bfmeSlot922D02();
	virtual void bfmeSlot922D03();
	virtual void bfmeSlot922D04();
	virtual void bfmeSlot922D05();
	virtual void bfmeSlot922D06();
	virtual void bfmeSlot922D07();
	virtual void bfmeSlot922D08();
	virtual void bfmeSlot922D09();
	virtual void bfmeSlot922D10();
	virtual void bfmeSlot922D11();
	virtual void bfmeSlot922D12();
	virtual void bfmeSlot922D13();
	virtual void bfmeSlot922D14();
	virtual void bfmeSlot922D15();
	virtual void bfmeSlot922D16();
	virtual void bfmeSlot922D17();
	virtual void bfmeSlot922D18();
	virtual void bfmeSlot922D19();
	virtual void bfmeSlot922D20();
	virtual void bfmeSlot922D21();
	virtual void bfmeSlot922D22();
	virtual void bfmeSlot922D23();
	virtual void bfmeSlot922D24();
	virtual void bfmeSlot922D25();
	virtual void bfmeVirt922D(void *a);
};

extern BfmeGlob922D *g_bfme922GlobD;

char __stdcall bfmeGo922D(void *a, void *b, void *c)
{
	if (a && c)
		g_bfme922GlobD->bfmeVirt922D(a);
	return 0;
}

class BfmeTail922F
{
public:
	void bfmeCall922F(void *a, int f);
};

struct BfmeS922F
{
	char m_bfmePad[0x20];
	BfmeTail922F m_bfmeTail;
};

struct BfmeO922F
{
	char m_bfmePad[0x204];
	BfmeS922F *m_bfmeS;
};

class BfmeThing922F
{
public:
	void bfmeGo922F(void *a);
};

void BfmeThing922F::bfmeGo922F(void *a)
{
	BfmeO922F *o = *(BfmeO922F **)((char *)this - 0x18);
	BfmeS922F *s = o->m_bfmeS;
	if (s)
		s->m_bfmeTail.bfmeCall922F(a, 2);
}

struct BfmeArg922G
{
	char m_bfmePad[0x74];
	void *m_bfmeVal;
};

class BfmeSub922G
{
public:
	void bfmeCall922G(void **p);
};

class BfmeThing922G
{
public:
	void bfmeGo922G(BfmeArg922G *a);
	char m_bfmePad[0x24];
	BfmeSub922G m_bfmeSub;
};

void BfmeThing922G::bfmeGo922G(BfmeArg922G *a)
{
	if (a) {
		void *p = a->m_bfmeVal;
		m_bfmeSub.bfmeCall922G(&p);
	}
}
