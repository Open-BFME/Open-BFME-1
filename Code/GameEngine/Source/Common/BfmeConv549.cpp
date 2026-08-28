class BfmeThingBXB
{
public:
	BfmeThingBXB *bfmeGoBXB(BfmeThingBXB *other);
	unsigned char m_bfmeHead[4];
	int m_bfmeVal;
};

int bfmeCalcBXB(int value, unsigned int seed);

BfmeThingBXB *BfmeThingBXB::bfmeGoBXB(BfmeThingBXB *other)
{
	int value = bfmeCalcBXB(m_bfmeVal, 0xBA792210u);
	m_bfmeVal = value;
	other->m_bfmeVal = value;
	return other;
}
