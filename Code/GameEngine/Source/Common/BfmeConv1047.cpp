// Open-BFME5 conversions.

inline void *operator new(unsigned int, void *p) { return p; }

void *bfmeAlloc1047(int n);

struct BfmeValI1047
{
	BfmeValI1047(int x) { m_bfmeX = x; }

	int m_bfmeX;
};

struct BfmeNodeI1047
{
	BfmeNodeI1047 *m_bfmeNext;
	BfmeNodeI1047 *m_bfmePrev;
	BfmeValI1047 m_bfmeV;
};

class BfmeA1047
{
public:
	void bfmeGo1047A(int i, int v);

	char m_bfmePad[0xf4];
	BfmeNodeI1047 *m_bfmeHeads[1];
};

void BfmeA1047::bfmeGo1047A(int i, int v)
{
	BfmeNodeI1047 *h = m_bfmeHeads[i];
	BfmeNodeI1047 *n = (BfmeNodeI1047 *)bfmeAlloc1047(0xc);

	new (&n->m_bfmeV) BfmeValI1047(v);

	BfmeNodeI1047 *t = h->m_bfmePrev;

	n->m_bfmeNext = h;
	n->m_bfmePrev = t;
	t->m_bfmeNext = n;
	h->m_bfmePrev = n;
}

struct BfmeValW1047
{
	BfmeValW1047(unsigned short x) { m_bfmeX = x; }

	unsigned short m_bfmeX;
};

struct BfmeNodeW1047
{
	BfmeNodeW1047 *m_bfmeNext;
	BfmeNodeW1047 *m_bfmePrev;
	BfmeValW1047 m_bfmeV;
};

struct BfmeQ1047
{
	char m_bfmePad[0x478];
	unsigned short m_bfmeId;
};

class BfmeB1047
{
public:
	void bfmeGo1047B(BfmeQ1047 *q);

	char m_bfmePad[0x64c];
	BfmeNodeW1047 *m_bfmeHead;
};

void BfmeB1047::bfmeGo1047B(BfmeQ1047 *q)
{
	BfmeNodeW1047 *h = m_bfmeHead;
	unsigned short w = q->m_bfmeId;
	BfmeNodeW1047 *n = (BfmeNodeW1047 *)bfmeAlloc1047(0xc);

	new (&n->m_bfmeV) BfmeValW1047(w);

	BfmeNodeW1047 *t = h->m_bfmePrev;

	n->m_bfmeNext = h;
	n->m_bfmePrev = t;
	t->m_bfmeNext = n;
	h->m_bfmePrev = n;
}

struct BfmeValS1047
{
	char m_bfmePad[4];
};

struct BfmeNodeS1047
{
	BfmeNodeS1047 *m_bfmeNext;
	BfmeNodeS1047 *m_bfmePrev;
	BfmeValS1047 m_bfmeV;
};

void bfmeInitVal1047(BfmeValS1047 *v, int a);

class BfmeD1047
{
public:
	void bfmeGo1047D(int a);
	void bfmeGo1047E(int a);

	char m_bfmePad[0x17260];
	BfmeNodeS1047 *m_bfmeHeadA;
	char m_bfmePad2[8];
	BfmeNodeS1047 *m_bfmeHeadB;
};

void BfmeD1047::bfmeGo1047D(int a)
{
	BfmeNodeS1047 *h = m_bfmeHeadA;
	BfmeNodeS1047 *n = (BfmeNodeS1047 *)bfmeAlloc1047(0xc);

	bfmeInitVal1047(&n->m_bfmeV, a);

	BfmeNodeS1047 *t = h->m_bfmePrev;

	n->m_bfmeNext = h;
	n->m_bfmePrev = t;
	t->m_bfmeNext = n;
	h->m_bfmePrev = n;
}

void BfmeD1047::bfmeGo1047E(int a)
{
	BfmeNodeS1047 *h = m_bfmeHeadB;
	BfmeNodeS1047 *n = (BfmeNodeS1047 *)bfmeAlloc1047(0xc);

	bfmeInitVal1047(&n->m_bfmeV, a);

	BfmeNodeS1047 *t = h->m_bfmePrev;

	n->m_bfmeNext = h;
	n->m_bfmePrev = t;
	t->m_bfmeNext = n;
	h->m_bfmePrev = n;
}

struct BfmeSNode1047
{
	BfmeSNode1047 *volatile m_bfmeNext;
	BfmeValI1047 m_bfmeV;
};

class BfmeF1047
{
public:
	void bfmeGo1047F(int *p);

	BfmeSNode1047 *m_bfmeHead;
};

void BfmeF1047::bfmeGo1047F(int *p)
{
	BfmeSNode1047 *n = (BfmeSNode1047 *)bfmeAlloc1047(8);

	new (&n->m_bfmeV) BfmeValI1047(*p);

	n->m_bfmeNext = 0;
	n->m_bfmeNext = m_bfmeHead;
	m_bfmeHead = n;
}

