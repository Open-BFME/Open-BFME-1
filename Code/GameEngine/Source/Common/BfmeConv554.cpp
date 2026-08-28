class BfmeThingBXG
{
public:
	BfmeThingBXG *bfmeGoBXG(BfmeThingBXG *other);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

int bfmeCalcBXG(int value, unsigned int seed);

BfmeThingBXG *BfmeThingBXG::bfmeGoBXG(BfmeThingBXG *other)
{
	int value = bfmeCalcBXG(m_bfmeVal, 0x0790A442u);
	m_bfmeVal = value;
	other->m_bfmeVal = value;
	return other;
}
