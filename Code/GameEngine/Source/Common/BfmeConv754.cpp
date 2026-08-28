class BfmeOtherDPG
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubDPG
{
public:
	void bfmeCallDPG(BfmeOtherDPG *other);
};

class BfmeThingDPG
{
public:
	BfmeOtherDPG *bfmeGoDPG(BfmeOtherDPG *other);
	unsigned char m_bfmeHead[0x30];
	BfmeSubDPG m_bfmeSub;
};

BfmeOtherDPG *BfmeThingDPG::bfmeGoDPG(BfmeOtherDPG *other)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeCallDPG(other);
	return other;
}
