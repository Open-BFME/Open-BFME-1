class BfmeThingBXC
{
public:
	BfmeThingBXC *bfmeGoBXC(BfmeThingBXC *other, int spare);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

int bfmeCalcBXC(int value, unsigned int seed);

BfmeThingBXC *BfmeThingBXC::bfmeGoBXC(BfmeThingBXC *other, int spare)
{
	int old = m_bfmeVal;
	m_bfmeVal = bfmeCalcBXC(old, 0xBA792210u);
	other->m_bfmeVal = old;
	return other;
}
