// Open-BFME5 conversions.

class BfmeGlob935A
{
public:
	void bfmeCall935A();
};

extern BfmeGlob935A *g_bfme935GlobA;

void __stdcall bfmeGo935A(void *a)
{
	BfmeGlob935A *g = g_bfme935GlobA;
	if (g)
		g->bfmeCall935A();
}

class BfmeSub935B
{
public:
	char bfmeTail935B();
};

class BfmeThing935B
{
public:
	char bfmeGo935B();
	char m_bfmePad[0xc];
	char m_bfmeFlag;
};

char BfmeThing935B::bfmeGo935B()
{
	if (!m_bfmeFlag)
		return 0;
	return ((BfmeSub935B *)((char *)this + 0x58))->bfmeTail935B();
}

struct BfmeObj935C
{
	char m_bfmePad[0x26c];
	char m_bfmeFlag;
};

extern BfmeObj935C *g_bfme935GlobC;
void bfmeTail935C(void);

void bfmeGo935C(void)
{
	BfmeObj935C *p = g_bfme935GlobC;
	if (p) {
		p->m_bfmeFlag = 1;
		return;
	}
	bfmeTail935C();
}

class BfmeSub935E
{
public:
	void bfmeCall935E(void *a);
};

class BfmeThing935E
{
public:
	void bfmeGo935E(void *a, void *b);
};

void BfmeThing935E::bfmeGo935E(void *a, void *b)
{
	((BfmeSub935E *)((char *)this + 0x9c))->bfmeCall935E(a);
}

class BfmeSub935F
{
public:
	void bfmeCall935F(void **a);
};

class BfmeThing935F
{
public:
	void bfmeGo935F(void *a);
};

void BfmeThing935F::bfmeGo935F(void *a)
{
	((BfmeSub935F *)((char *)this + 0x6e0))->bfmeCall935F(&a);
}

void __stdcall bfmeCall935G(void *a, int b, int c, int d);

void __stdcall bfmeGo935G(void *a)
{
	bfmeCall935G(a, 0, 0, 1);
}

class BfmeObj935H
{
public:
	void bfmeTail935H();
};

class BfmeThing935H
{
public:
	void bfmeGo935H();
	BfmeObj935H *m_bfmeP;
};

void BfmeThing935H::bfmeGo935H()
{
	BfmeObj935H *o = m_bfmeP;
	int d = *(int *)(*(char **)o + 4);
	unsigned int bits = *(unsigned int *)((char *)o + d + 4);
	if (bits & 0x2000)
		o->bfmeTail935H();
}
