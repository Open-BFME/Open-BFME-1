class BfmeSubDPE
{
	unsigned char m_bfmeHead[4];
};

class BfmeFirstDPE
{
public:
	BfmeSubDPE m_bfmeSub;
};

class BfmeOtherDPE
{
public:
	void bfmeCallDPE(BfmeSubDPE *sub);
};

class BfmeThingDPE
{
public:
	BfmeOtherDPE *bfmeGoDPE(BfmeOtherDPE *other);
	BfmeFirstDPE *m_bfmeFirst;
};

BfmeOtherDPE *BfmeThingDPE::bfmeGoDPE(BfmeOtherDPE *other)
{
	volatile int tmp = 0;
	other->bfmeCallDPE(&m_bfmeFirst->m_bfmeSub);
	return other;
}
