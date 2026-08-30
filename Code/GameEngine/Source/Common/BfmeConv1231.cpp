// Open-BFME5 conversions.

class BfmeE1231
{
public:
	virtual void bfmeV1231A();
	virtual void bfmeV1231B();
	void *bfmeVal1231();
	unsigned m_bfme04;
};

class BfmeB1231
{
public:
	int m_bfme00;
	void *m_bfme04;
	void *m_bfme08;
};

class BfmeA1231
{
public:
	void bfmeEmit1231(void *a1, void *a2, BfmeE1231 *a3, BfmeE1231 *a4, void *a5, int a6);
	int m_bfme00;
	int m_bfme04;
	BfmeE1231 **m_bfme08;
};

void bfmeGo1231(BfmeA1231 *a, BfmeB1231 *b)
{
	BfmeE1231 *e1;
	BfmeE1231 *e2;
	BfmeE1231 *e3;
	BfmeE1231 *e;
	void *v;
	int i;

	e1 = a->m_bfme08[a->m_bfme00 - 1];
	e2 = a->m_bfme08[a->m_bfme00 - 2];
	e3 = a->m_bfme08[a->m_bfme00 - 3];
	v = e1->bfmeVal1231();
	a->bfmeEmit1231(b->m_bfme04, b->m_bfme08, e3, e2, v, 0);
	for (i = 1; i <= 3; ++i) {
		e = a->m_bfme08[a->m_bfme00 - i];
		if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
			e->bfmeV1231B();
	}
	a->m_bfme00 -= 3;
}
