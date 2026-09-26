// ?bfmeAddAAD@BfmeHostAAD@@QAEXVBfmeUniStrAAD@@G@Z
// partial score=0.97 date=2026-09-08
void *Rva0082E540NodeAllocate(unsigned int n);

class BfmeUniStrAAD
{
public:
	BfmeUniStrAAD() { m_bfmeDataAAD = 0; }
	~BfmeUniStrAAD() { bfmeReleaseAAD(); }

	void bfmeSetAAD(const BfmeUniStrAAD &o);

	void *m_bfmeDataAAD;

private:
	void bfmeReleaseAAD();
};

struct BfmePairAAD
{
	BfmeUniStrAAD m_bfmeFirstAAD;
	unsigned short m_bfmeSecondAAD;
};

void bfmeConstructAAD(BfmePairAAD *dst, const BfmePairAAD &src);

struct BfmeNodeAAD
{
	BfmeNodeAAD *m_bfmePrevAAD;
	BfmeNodeAAD *m_bfmeNextAAD;
	BfmePairAAD m_bfmeValAAD;
};

class BfmeHostAAD
{
public:
	void bfmeAddAAD(BfmeUniStrAAD name, unsigned short id);

	unsigned char m_bfmeHeadAAD[0x1ac];
	BfmeNodeAAD *m_bfme1ACAAD;
};

void BfmeHostAAD::bfmeAddAAD(BfmeUniStrAAD name, unsigned short id)
{
	BfmePairAAD p;

	p.m_bfmeFirstAAD.bfmeSetAAD(name);
	p.m_bfmeSecondAAD = id;

	BfmeNodeAAD *h = m_bfme1ACAAD;
	BfmeNodeAAD *n = (BfmeNodeAAD *)Rva0082E540NodeAllocate(16);

	bfmeConstructAAD(&n->m_bfmeValAAD, p);

	BfmeNodeAAD *nx = h->m_bfmeNextAAD;

	n->m_bfmePrevAAD = h;
	n->m_bfmeNextAAD = nx;
	nx->m_bfmePrevAAD = n;
	h->m_bfmeNextAAD = n;
}
