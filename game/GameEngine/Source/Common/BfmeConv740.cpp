class BfmeItemDOA
{
	unsigned char m_bfmeHead[4];
};

class BfmeOtherDOA
{
public:
	void bfmeCallDOA(BfmeItemDOA *item);
};

class BfmeThingDOA
{
public:
	BfmeOtherDOA *bfmeGoDOA(BfmeOtherDOA *other, int index);
	unsigned char m_bfmeHead[0x48];
	BfmeItemDOA m_bfmeItems[8];
};

BfmeOtherDOA *BfmeThingDOA::bfmeGoDOA(BfmeOtherDOA *other, int index)
{
	volatile int tmp = 0;
	other->bfmeCallDOA(&m_bfmeItems[index]);
	return other;
}
