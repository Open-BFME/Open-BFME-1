// Open-BFME5 conversions.

class AptValue
{
public:
	virtual void bfmeV1218A();
	virtual void bfmeV1218B();
	bool rva00898480Check();
	unsigned m_bfme04;
};

class BfmeA1218
{
public:
	int m_bfme00;
	int m_bfme04;
	AptValue **m_bfme08;
};

class BfmeG1218
{
public:
	void bfmeStep1218C();
	int m_bfme00;
	int m_bfme04;
};

struct Rva00899560Pool;

extern Rva00899560Pool *g_rva01337810GcRoots;

void bfmeGo1218(BfmeA1218 *a, const unsigned char **b)
{
	const unsigned char *p;
	AptValue *e;
	BfmeG1218 *g;

	p = (const unsigned char *)(((unsigned int)*b + 3) & 0xfffffffc);
	*b = p + 4;
	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1218B();
	--a->m_bfme00;
	if (e->rva00898480Check() == 1)
		*b += *(const int *)p;
	g = (BfmeG1218 *)g_rva01337810GcRoots;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		g->bfmeStep1218C();
}
