class BfmeItemDOC
{
	unsigned char m_bfmeHead[4];
};

class BfmeOtherDOC
{
public:
	void bfmeCallDOC(BfmeItemDOC *item);
};

class BfmeThingDOC
{
public:
	BfmeOtherDOC *bfmeGoDOC(BfmeOtherDOC *other, int index);
	unsigned char m_bfmeHead[0x38];
	BfmeItemDOC m_bfmeItems[8];
};

BfmeOtherDOC *BfmeThingDOC::bfmeGoDOC(BfmeOtherDOC *other, int index)
{
	volatile int tmp = 0;
	other->bfmeCallDOC(&m_bfmeItems[index]);
	return other;
}
