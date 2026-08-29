// Open-BFME5 conversions.

inline void *operator new(unsigned int, void *p) { return p; }

void *bfmeAlloc1046(int n);

struct BfmeVal1046
{
	BfmeVal1046(int x) { m_bfmeX = x; }

	int m_bfmeX;
};

struct BfmeNode1046
{
	BfmeNode1046 *m_bfmeNext;
	BfmeNode1046 *m_bfmePrev;
	BfmeVal1046 m_bfmeV;
};

class BfmeA1046
{
public:
	void bfmeGo1046A(int v);

	char m_bfmePad[8];
	BfmeNode1046 *m_bfmeHead;
	char m_bfmePad2[4];
	int m_bfmeCount;
};

void BfmeA1046::bfmeGo1046A(int v)
{
	BfmeNode1046 *h = m_bfmeHead;
	BfmeNode1046 *n = (BfmeNode1046 *)bfmeAlloc1046(0xc);

	new (&n->m_bfmeV) BfmeVal1046(v);

	BfmeNode1046 *t = h->m_bfmePrev;

	n->m_bfmeNext = h;
	n->m_bfmePrev = t;
	t->m_bfmeNext = n;
	h->m_bfmePrev = n;
	m_bfmeCount++;
}

struct BfmeSubA1046
{
	char m_bfmePad[4];
};

struct BfmeSubB1046
{
	char m_bfmePad[4];
};

struct BfmeC1046
{
	char m_bfmePad[0x18d8];
	BfmeSubA1046 m_bfmeSubA;
	char m_bfmePad2[0x5c8];
	BfmeSubB1046 m_bfmeSubB;
	char m_bfmePad3[0x44];
	int m_bfme1eec;
};

void bfmeStepA1046(BfmeSubA1046 *p);
void bfmeStepB1046(BfmeSubB1046 *p);

void bfmeGo1046B(BfmeC1046 *p)
{
	if (*(int *)((char *)p + 0xba0) == 0)
		return;

	p->m_bfme1eec = 0;
	bfmeStepA1046(&p->m_bfmeSubA);
	bfmeStepB1046(&p->m_bfmeSubB);
}

class BfmeQ1046
{
public:
	virtual void bfmeV01046();
	virtual void bfmeV11046();
	virtual void bfmeStop1046();

	char m_bfmePad[0x4c];
	int m_bfme50;
};

struct BfmeE1046
{
	BfmeQ1046 *m_bfmeQ;
};

extern void (__cdecl *g_bfmeFree1046)(void *p, int n);

class BfmeD1046
{
public:
	void bfmeGo1046D(void);
	void bfmeReset1046(int n);

	BfmeE1046 *m_bfmeP;
};

void BfmeD1046::bfmeGo1046D(void)
{
	bfmeReset1046(0);

	BfmeE1046 *p = m_bfmeP;

	if (p != 0) {
		p->m_bfmeQ->m_bfme50 = 0;
		p->m_bfmeQ->bfmeStop1046();
		g_bfmeFree1046(p, 4);
	}

	m_bfmeP = 0;
}
