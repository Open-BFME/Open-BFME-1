class BfmeSubDQC
{
public:
	unsigned char m_bfmeHead[0x84];
	unsigned char m_bfmeTail[4];
};

class BfmeOtherDQC
{
public:
	void bfmeCallDQC(void *what);
};

class BfmeThingDQC
{
public:
	BfmeOtherDQC *bfmeGoDQC(BfmeOtherDQC *other);
	unsigned char m_bfmeHead[4];
	BfmeSubDQC *m_bfmeSub;
};

BfmeOtherDQC *BfmeThingDQC::bfmeGoDQC(BfmeOtherDQC *other)
{
	volatile int tmp = 0;
	other->bfmeCallDQC(m_bfmeSub->m_bfmeTail);
	return other;
}
