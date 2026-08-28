struct BfmeSubEIB
{
	unsigned char m_bfmeHead[0x10];
	int m_bfmeX;
};

class BfmeOtherEIB
{
public:
	void bfmeCallEIB(int *x);
};

struct BfmeThingEIB
{

	BfmeOtherEIB *bfmeGoEIBa(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBb(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBc(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBd(BfmeOtherEIB *other);
	BfmeOtherEIB *bfmeGoEIBe(BfmeOtherEIB *other);
	BfmeSubEIB *bfmeMakeEIB();
	unsigned char m_bfmeHead[4];
	BfmeSubEIB *m_bfmeP;
};

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBa(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	BfmeSubEIB *p = m_bfmeP;
	if (!p)
		p = bfmeMakeEIB();
	other->bfmeCallEIB(&p->m_bfmeX);
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBb(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	BfmeSubEIB *p = m_bfmeP;
	if (!p)
		p = bfmeMakeEIB();
	other->bfmeCallEIB(&p->m_bfmeX);
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBc(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	BfmeSubEIB *p = m_bfmeP;
	if (!p)
		p = bfmeMakeEIB();
	other->bfmeCallEIB(&p->m_bfmeX);
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBd(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	BfmeSubEIB *p = m_bfmeP;
	if (!p)
		p = bfmeMakeEIB();
	other->bfmeCallEIB(&p->m_bfmeX);
	return other;
}

BfmeOtherEIB *BfmeThingEIB::bfmeGoEIBe(BfmeOtherEIB *other)
{
	volatile int tmp = 0;
	BfmeSubEIB *p = m_bfmeP;
	if (!p)
		p = bfmeMakeEIB();
	other->bfmeCallEIB(&p->m_bfmeX);
	return other;
}

