class BfmeThingBXA
{
public:
	BfmeThingBXA *bfmeGoBXA(BfmeThingBXA *other);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

int bfmeCalcBXA(int value, unsigned int seed);

BfmeThingBXA *BfmeThingBXA::bfmeGoBXA(BfmeThingBXA *other)
{
	int value = bfmeCalcBXA(m_bfmeVal, 0x352D2FF1u);
	m_bfmeVal = value;
	other->m_bfmeVal = value;
	return other;
}
