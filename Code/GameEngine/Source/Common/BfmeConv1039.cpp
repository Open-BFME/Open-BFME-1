// Open-BFME5 conversions.

extern "C" void *bfmeVft1039C[];
extern "C" void *bfmeVft1039D[];

class BfmeD1039;

class BfmeC1039
{
public:
	void bfmeInit1039(BfmeD1039 *o);

	void *m_bfmeVfptr;
};

void *bfmeAlloc1039(int n);

class BfmeD1039
{
public:
	BfmeC1039 *bfmeGo1039C(void);
	BfmeC1039 *bfmeGo1039D(void);
};

BfmeC1039 *BfmeD1039::bfmeGo1039C(void)
{
	BfmeC1039 *p = (BfmeC1039 *)bfmeAlloc1039(0x34);

	if (p != 0) {
		p->bfmeInit1039(this);
		p->m_bfmeVfptr = bfmeVft1039C;
		return p;
	}

	return 0;
}

BfmeC1039 *BfmeD1039::bfmeGo1039D(void)
{
	BfmeC1039 *p = (BfmeC1039 *)bfmeAlloc1039(0x34);

	if (p != 0) {
		p->bfmeInit1039(this);
		p->m_bfmeVfptr = bfmeVft1039D;
		return p;
	}

	return 0;
}

struct BfmeRec1039
{
	int m_bfmeKind;
	char m_bfmePad[4];
	int m_bfmeVal;
	char m_bfmePad2[4];
};

struct BfmeQ1039
{
	BfmeRec1039 *m_bfmeCur;
	char m_bfmePad[4];
	BfmeRec1039 *m_bfmeEnd;
};

void bfmeGrow1039(BfmeQ1039 *q, int n);

void bfmeGo1039E(BfmeQ1039 *q, int v)
{
	q->m_bfmeCur->m_bfmeKind = 6;
	q->m_bfmeCur->m_bfmeVal = v;

	if (q->m_bfmeCur == q->m_bfmeEnd)
		bfmeGrow1039(q, 1);

	q->m_bfmeCur++;
}
