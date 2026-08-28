class BfmeThingBXH
{
public:
	BfmeThingBXH *bfmeGoBXH(BfmeThingBXH *other, int spare);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

int bfmeCalcBXH(int value, unsigned int seed);

BfmeThingBXH *BfmeThingBXH::bfmeGoBXH(BfmeThingBXH *other, int spare)
{
	int old = m_bfmeVal;
	m_bfmeVal = bfmeCalcBXH(old, 0x0790A442u);
	other->m_bfmeVal = old;
	return other;
}
