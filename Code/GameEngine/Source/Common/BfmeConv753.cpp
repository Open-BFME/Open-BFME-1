class BfmeSubDPF
{
	unsigned char m_bfmeHead[4];
};

class BfmeFirstDPF
{
public:
	unsigned char m_bfmeHead[0xc];
	BfmeSubDPF m_bfmeSub;
};

class BfmeOtherDPF
{
public:
	void bfmeCallDPF(BfmeSubDPF *sub);
};

class BfmeThingDPF
{
public:
	BfmeOtherDPF *bfmeGoDPF(BfmeOtherDPF *other);
	BfmeFirstDPF *m_bfmeFirst;
};

BfmeOtherDPF *BfmeThingDPF::bfmeGoDPF(BfmeOtherDPF *other)
{
	volatile int tmp = 0;
	other->bfmeCallDPF(&m_bfmeFirst->m_bfmeSub);
	return other;
}
