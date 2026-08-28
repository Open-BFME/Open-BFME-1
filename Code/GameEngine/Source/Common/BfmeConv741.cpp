class BfmeItemDOB
{
	unsigned char m_bfmeHead[4];
};

class BfmeOtherDOB
{
public:
	void bfmeCallDOB(BfmeItemDOB *item);
};

class BfmeThingDOB
{
public:
	BfmeOtherDOB *bfmeGoDOB(BfmeOtherDOB *other, int index);
	unsigned char m_bfmeHead[0x54];
	BfmeItemDOB m_bfmeItems[8];
};

BfmeOtherDOB *BfmeThingDOB::bfmeGoDOB(BfmeOtherDOB *other, int index)
{
	volatile int tmp = 0;
	other->bfmeCallDOB(&m_bfmeItems[index]);
	return other;
}
