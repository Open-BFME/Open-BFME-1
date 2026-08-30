// Open-BFME5 conversions.

class BfmeE1217
{
public:
	virtual void bfmeV1217A();
	virtual void bfmeV1217B();
	unsigned m_bfme04;
};

class BfmeA1217
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1217 **m_bfme08;
	char m_bfmePad0c[0x80 - 0x0c];
	int m_bfme80;
};

class BfmeG1217
{
public:
	void bfmeStep1217C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1217 *g_bfme1217;

void bfmeGo1217(BfmeA1217 *a, const unsigned char **b)
{
	int n;
	BfmeE1217 *e;
	BfmeG1217 *g;

	n = a->m_bfme00;
	if (n > a->m_bfme80) {
		e = a->m_bfme08[n - 1];
		if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
			e->bfmeV1217B();
		--a->m_bfme00;
	}
	if (n == 1) {
		g = g_bfme1217;
		if (g->m_bfme04)
			g->bfmeStep1217C();
	}
}
