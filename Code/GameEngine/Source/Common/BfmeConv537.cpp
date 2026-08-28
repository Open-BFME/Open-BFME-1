class BfmeSubBVB
{
public:
	void bfmeOneBVB();
	void bfmeTwoBVB(BfmeSubBVB *other);
};

class BfmeThingBVB
{
public:
	void bfmeGoBVB(BfmeThingBVB *other);
	unsigned char m_bfmeHead[0x630];
	BfmeSubBVB m_bfmeSub;
};

void BfmeThingBVB::bfmeGoBVB(BfmeThingBVB *other)
{
	BfmeSubBVB *sub = &m_bfmeSub;
	sub->bfmeOneBVB();
	sub->bfmeTwoBVB(&other->m_bfmeSub);
}
