class BfmeSubEFJ
{
	unsigned char m_bfmeHead[4];
};

class BfmeResEFJ
{
public:
	void bfmeUseEFJ(void *a, void *b);
};

class BfmeGlobEFJ
{
public:
	BfmeResEFJ *bfmeLookEFJ(BfmeSubEFJ *s);
};

extern BfmeGlobEFJ *g_bfmeObjEFJ;

struct BfmeThingEFJa
{
	void bfmeGoEFJa(void *a, void *b);
	unsigned char m_bfmeHead[0x5c];
	BfmeSubEFJ m_bfmeSub;
};

void BfmeThingEFJa::bfmeGoEFJa(void *a, void *b)
{
	BfmeResEFJ *r = g_bfmeObjEFJ->bfmeLookEFJ(&m_bfmeSub);
	if (r)
		r->bfmeUseEFJ(a, b);
}

struct BfmeThingEFJb
{
	void bfmeGoEFJb(void *a, void *b);
	unsigned char m_bfmeHead[0xb4];
	BfmeSubEFJ m_bfmeSub;
};

void BfmeThingEFJb::bfmeGoEFJb(void *a, void *b)
{
	BfmeResEFJ *r = g_bfmeObjEFJ->bfmeLookEFJ(&m_bfmeSub);
	if (r)
		r->bfmeUseEFJ(a, b);
}
