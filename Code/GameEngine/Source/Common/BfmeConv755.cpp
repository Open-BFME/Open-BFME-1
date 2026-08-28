class BfmeOtherDPH
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubDPH
{
public:
	void bfmeCallDPH(BfmeOtherDPH *other);
};

class BfmeThingDPH
{
public:
	BfmeOtherDPH *bfmeGoDPH(BfmeOtherDPH *other);
	unsigned char m_bfmeHead[0x170];
	BfmeSubDPH m_bfmeSub;
};

BfmeOtherDPH *BfmeThingDPH::bfmeGoDPH(BfmeOtherDPH *other)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeCallDPH(other);
	return other;
}
