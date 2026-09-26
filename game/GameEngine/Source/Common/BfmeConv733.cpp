class BfmeSubDNA
{
	unsigned char m_bfmeHead[4];
};

struct BfmeOwnerDNA
{
	unsigned char m_bfmeHead[8];
	BfmeSubDNA m_bfmeSub;
};

class BfmeOtherDNA
{
public:
	void bfmeCallDNA(BfmeSubDNA *sub);
};

struct BfmeThingDNA
{
	BfmeOtherDNA *bfmeGoDNA(BfmeOtherDNA *other);
};

BfmeOtherDNA *BfmeThingDNA::bfmeGoDNA(BfmeOtherDNA *other)
{
	volatile int tmp = 0;
	BfmeOwnerDNA *owner = *(BfmeOwnerDNA **)((char *)this - 0x1c);
	other->bfmeCallDNA(&owner->m_bfmeSub);
	return other;
}
