// Open-BFME5 conversions.

void bfmeFree1041(char *p);

class BfmeC1041
{
public:
	void bfmeGo1041C(void);
	void bfmeGo1041C2(void);

	char *m_bfmeP;
	char *m_bfmeBuf;
	char *m_bfmeEnd;
	char **m_bfmeCur;
};

void BfmeC1041::bfmeGo1041C(void)
{
	if (m_bfmeBuf != 0)
		bfmeFree1041(m_bfmeBuf);

	m_bfmeCur++;
	m_bfmeBuf = *m_bfmeCur;
	m_bfmeEnd = m_bfmeBuf + 0x2b8;
	m_bfmeP = m_bfmeBuf;
}

void BfmeC1041::bfmeGo1041C2(void)
{
	if (m_bfmeBuf != 0)
		bfmeFree1041(m_bfmeBuf);

	m_bfmeCur++;
	m_bfmeBuf = *m_bfmeCur;
	m_bfmeEnd = m_bfmeBuf + 0x864;
	m_bfmeP = m_bfmeBuf;
}

struct BfmeQ1041
{
	char m_bfmePad[0x504];
	void *m_bfmeR;
};

extern char g_bfmeFmt1041[];
int bfmeCount1041(int a, void *p, char *f, int n);

class BfmeE1041
{
public:
	void bfmeGo1041E(void);

	char m_bfmePad[4];
	BfmeQ1041 *m_bfmeQ;
	char m_bfmePad2[0x50];
	int m_bfmeVal;
};

void BfmeE1041::bfmeGo1041E(void)
{
	void *p = m_bfmeQ->m_bfmeR;
	int r;

	if (p != 0)
		r = bfmeCount1041(0, p, g_bfmeFmt1041, 0xcdc);
	else
		r = 0;

	m_bfmeVal = r;
}

struct BfmeRc1041
{
	unsigned short m_bfmeCount;
};

struct BfmeAlloc1041
{
	void *m_bfmePad;
	void (__cdecl *m_bfmeFree)(BfmeRc1041 *r);
};

extern BfmeAlloc1041 *g_bfmeAlloc1041;

class BfmeF1041
{
public:
	BfmeF1041 *bfmeGo1041F(BfmeF1041 *o);

	BfmeRc1041 *m_bfmeRc;
};

BfmeF1041 *BfmeF1041::bfmeGo1041F(BfmeF1041 *o)
{
	o->m_bfmeRc->m_bfmeCount++;

	BfmeRc1041 *r = m_bfmeRc;

	r->m_bfmeCount--;

	if (r->m_bfmeCount == 0)
		g_bfmeAlloc1041->m_bfmeFree(r);

	m_bfmeRc = o->m_bfmeRc;
	return this;
}

