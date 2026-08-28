struct BfmePartCKA
{
	void bfmeCopyOneCKA(BfmePartCKA *other);
	void bfmeCopyTwoCKA(BfmePartCKA *other);
	unsigned char m_bfmeHead[0xc];
};

struct BfmeThingCKA
{
	void bfmeBaseCKA(BfmeThingCKA *other);
	BfmeThingCKA *bfmeGoCKA(BfmeThingCKA *other);
	unsigned char m_bfmeHead[0xc];
	BfmePartCKA m_bfmeA;
	BfmePartCKA m_bfmeB;
};

BfmeThingCKA *BfmeThingCKA::bfmeGoCKA(BfmeThingCKA *other)
{
	bfmeBaseCKA(other);
	m_bfmeA.bfmeCopyOneCKA(&other->m_bfmeA);
	m_bfmeB.bfmeCopyTwoCKA(&other->m_bfmeB);
	return this;
}
