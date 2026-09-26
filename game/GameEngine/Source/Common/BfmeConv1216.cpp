// Open-BFME5 conversions.

class BfmeE1216
{
public:
	virtual void bfmeV1216A();
	virtual void bfmeV1216B();
	unsigned m_bfme04;
};

class BfmeA1216
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1216 **m_bfme08;
	char m_bfmePad0c[0x60 - 0x0c];
	BfmeE1216 **m_bfme60;
};

class BfmeG1216
{
public:
	void bfmeStep1216C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1216 *g_bfme1216;

extern "C" void bfmeStep1216A(BfmeA1216 *a, const unsigned char **b);

void bfmeGo1216(BfmeA1216 *a, const unsigned char **b)
{
	const unsigned char *p;
	unsigned char c;
	BfmeE1216 *e;
	BfmeG1216 *g;

	p = *b;
	c = *p;
	*b = p + 1;
	e = a->m_bfme60[c];
	a->m_bfme08[a->m_bfme00] = e;
	++a->m_bfme00;
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1216A();
	bfmeStep1216A(a, b);
	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1216B();
	--a->m_bfme00;
	g = g_bfme1216;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		g->bfmeStep1216C();
}
