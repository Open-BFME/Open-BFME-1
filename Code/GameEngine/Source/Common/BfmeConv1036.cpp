// Open-BFME5 conversions.

__declspec(dllimport) int __stdcall bfmeWait1036(void *h, int t);

class BfmeA1036
{
public:
	BfmeA1036 *bfmeGo1036A(void *h);

	void *m_bfmeHandle;
	char m_bfmeOn;
};

BfmeA1036 *BfmeA1036::bfmeGo1036A(void *h)
{
	m_bfmeOn = 0;
	m_bfmeHandle = h;

	if (bfmeWait1036(h, -1) != 0x102)
		m_bfmeOn = 1;

	return this;
}

class BfmeSubB1036
{
public:
	char m_bfmePad[8];
	void *m_bfmeHead;
};

struct BfmeIt1036
{
	BfmeSubB1036 *m_bfmeOwner;
	void *m_bfmeCur;
};

void *bfmeAlloc1036(int n);

class BfmeB1036
{
public:
	BfmeIt1036 *bfmeGo1036B(void);

	char m_bfmePad[0x8c];
	BfmeSubB1036 m_bfmeSub;
};

BfmeIt1036 *BfmeB1036::bfmeGo1036B(void)
{
	BfmeIt1036 *p = (BfmeIt1036 *)bfmeAlloc1036(8);

	if (p != 0) {
		BfmeSubB1036 *s = &m_bfmeSub;

		p->m_bfmeOwner = s;
		p->m_bfmeCur = s->m_bfmeHead;
		return p;
	}

	return 0;
}

void bfmeRelease1036(void *p);

class BfmeE1036
{
public:
	void bfmeGo1036E(void);

	char m_bfmePad[8];
	void *m_bfmeP;
	char m_bfmePad2[0xc];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void BfmeE1036::bfmeGo1036E(void)
{
	int z = 0;

	if (m_bfmeP != 0) {
		bfmeRelease1036(m_bfmeP);
		m_bfmeP = (void *)z;
	}

	m_bfmeA = z;
	m_bfmeB = z;
	m_bfmeC = z;
}

