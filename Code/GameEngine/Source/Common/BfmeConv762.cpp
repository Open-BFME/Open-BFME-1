struct BfmeItemDQG
{
	void bfmeCallDQG(class BfmeOtherDQG *other);
	unsigned char m_bfmeHead[0x68];
};

class BfmeOtherDQG
{
	unsigned char m_bfmeHead[4];
};

class BfmeThingDQG
{
public:
	BfmeOtherDQG *bfmeGoDQG(BfmeOtherDQG *other, int index);
	unsigned char m_bfmeHead[0x58];
	BfmeItemDQG m_bfmeItems[8];
};

BfmeOtherDQG *BfmeThingDQG::bfmeGoDQG(BfmeOtherDQG *other, int index)
{
	volatile int tmp = 0;
	m_bfmeItems[index].bfmeCallDQG(other);
	return other;
}
