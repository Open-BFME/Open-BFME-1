// Open-BFME5 conversions.

extern "C" void *bfmeVft1045A[];
extern "C" void *bfmeVft1045B[];

class BfmeSub1045
{
public:
	void bfmeDone1045(void);

	char m_bfmePad[0x24];
};

class BfmeB1045
{
public:
	void bfmeGo1045B(void);

	void *m_bfmeVfptr;
	void *m_bfmeVfptr2;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	char m_bfmePad[0xd0];
	BfmeSub1045 m_bfmeArr[8];
};

void BfmeB1045::bfmeGo1045B(void)
{
	int z = 0;

	m_bfmeVfptr = bfmeVft1045A;
	m_bfmeVfptr2 = bfmeVft1045B;
	m_bfme08 = z;
	m_bfme0c = z;
	m_bfme10 = z;

	BfmeSub1045 *p = &m_bfmeArr[8];
	int n = 8;

	do {
		p--;
		p->bfmeDone1045();
	} while (--n != 0);
}

struct BfmeRc1045
{
	unsigned short m_bfmeCount;
};

struct BfmeAlloc1045
{
	void *m_bfmePad;
	void (__cdecl *m_bfmeFree)(BfmeRc1045 *r);
};

extern BfmeAlloc1045 *g_bfmeAlloc1045;

class BfmeG1045
{
public:
	BfmeG1045 *bfmeGo1045G(BfmeG1045 *o);

	BfmeRc1045 *m_bfmeRc;
	int m_bfmeVal;
};

BfmeG1045 *BfmeG1045::bfmeGo1045G(BfmeG1045 *o)
{
	o->m_bfmeRc->m_bfmeCount++;

	BfmeRc1045 *r = m_bfmeRc;

	r->m_bfmeCount--;

	if (r->m_bfmeCount == 0)
		g_bfmeAlloc1045->m_bfmeFree(r);

	m_bfmeRc = o->m_bfmeRc;
	m_bfmeVal = o->m_bfmeVal;
	return this;
}
