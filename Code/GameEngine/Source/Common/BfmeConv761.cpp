class BfmeOtherDQF
{
	unsigned char m_bfmeHead[4];
};

class BfmeSubDQF
{
public:
	void bfmeCallDQF(BfmeOtherDQF *other);
};

class BfmeThingDQF
{
public:
	BfmeOtherDQF *bfmeGoDQF(BfmeOtherDQF *other);
	unsigned char m_bfmeHead[0x130];
	BfmeSubDQF *m_bfmeSub;
};

BfmeOtherDQF *BfmeThingDQF::bfmeGoDQF(BfmeOtherDQF *other)
{
	volatile int tmp = 0;
	m_bfmeSub->bfmeCallDQF(other);
	return other;
}
