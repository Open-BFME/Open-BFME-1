// Open-BFME5 conversions.

class BfmeE1219
{
public:
	virtual void bfmeV1219A();
	virtual void bfmeV1219B();
	char bfmeChk1219();
	unsigned m_bfme04;
};

class BfmeA1219
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1219 **m_bfme08;
};

class BfmeG1219
{
public:
	void bfmeStep1219C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1219 *g_bfme1219;

void bfmeGo1219(BfmeA1219 *a, const unsigned char **b)
{
	const unsigned char *p;
	BfmeE1219 *e;
	BfmeG1219 *g;

	p = (const unsigned char *)(((unsigned int)*b + 3) & 0xfffffffc);
	*b = p + 4;
	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1219B();
	--a->m_bfme00;
	if (!e->bfmeChk1219())
		*b += *(const int *)p;
	g = g_bfme1219;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		g->bfmeStep1219C();
}
