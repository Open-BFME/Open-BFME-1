class BfmeOtherDOH;

class BfmeSubDOH
{
public:
	void bfmeCallDOH(BfmeOtherDOH *other);
};

class BfmeOtherDOH
{
	unsigned char m_bfmeHead[4];
};

class BfmeThingDOH
{
public:
	BfmeOtherDOH *bfmeGoDOH(BfmeOtherDOH *other);
	unsigned char m_bfmeHead[4];
	BfmeSubDOH *m_bfmeSub;
};

BfmeOtherDOH *BfmeThingDOH::bfmeGoDOH(BfmeOtherDOH *other)
{
	volatile int tmp = 0;
	m_bfmeSub->bfmeCallDOH(other);
	return other;
}
