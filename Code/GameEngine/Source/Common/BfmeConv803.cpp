class BfmeObjEBJ
{
public:
	void bfmeCallEBJ(void *b, const char *s);
};

extern "C" unsigned char bfmeStrEBJ[];

void __stdcall bfmeGoEBJ(BfmeObjEBJ *o, void *b)
{
	o->bfmeCallEBJ(b, (const char *)bfmeStrEBJ);
}

class BfmeObjEBK
{
public:
	void bfmeOneEBK(void *x, int n);
	void bfmeTwoEBK(void *x, void *b);
};

extern void *g_bfmeXEBK;

void __stdcall bfmeGoEBKa(BfmeObjEBK *o)
{
	o->bfmeOneEBK(g_bfmeXEBK, 0);
}

void __stdcall bfmeGoEBKb(BfmeObjEBK *o, void *b)
{
	o->bfmeTwoEBK(g_bfmeXEBK, b);
}

class BfmeObjEBL
{
public:
	void bfmeCallEBL(void *a, void *b);
	void *m_bfmeA;
	void *m_bfmeB;
};

extern BfmeObjEBL g_bfmeObjEBL;

void bfmeGoEBL()
{
	g_bfmeObjEBL.bfmeCallEBL(g_bfmeObjEBL.m_bfmeA, g_bfmeObjEBL.m_bfmeB);
}

char bfmeCmpEBMa(void *a, void *b);
char bfmeCmpEBMb(void *a, void *b);

bool bfmeGoEBMa(void *a, void *b)
{
	return bfmeCmpEBMa(a, b) == 0;
}

bool bfmeGoEBMb(void *a, void *b)
{
	return bfmeCmpEBMb(a, b) == 0;
}

struct BfmeSubEBN
{
	unsigned char m_bfmeHead[0x20];
	char m_bfmeC;
	unsigned char m_bfmePad[3];
	void *m_bfmeP;
};

class BfmeObjEBN
{
public:
	BfmeSubEBN *bfmeGetEBN();
};

void *bfmeGoEBNa(BfmeObjEBN *o)
{
	if (!o)
		return 0;
	BfmeSubEBN *s = o->bfmeGetEBN();
	if (!s)
		return 0;
	return s->m_bfmeP;
}

char bfmeGoEBNb(BfmeObjEBN *o)
{
	if (!o)
		return 0;
	BfmeSubEBN *s = o->bfmeGetEBN();
	if (!s)
		return 0;
	return s->m_bfmeC;
}
