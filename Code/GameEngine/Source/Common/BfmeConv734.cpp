class BfmeSubDNB
{
	unsigned char m_bfmeHead[4];
};

struct BfmeOwnerDNB
{
	unsigned char m_bfmeHead[0x2c];
	BfmeSubDNB m_bfmeSub;
};

class BfmeOtherDNB
{
public:
	void bfmeCallDNB(BfmeSubDNB *sub);
};

struct BfmeThingDNB
{
	BfmeOtherDNB *bfmeGoDNB(BfmeOtherDNB *other);
};

BfmeOtherDNB *BfmeThingDNB::bfmeGoDNB(BfmeOtherDNB *other)
{
	volatile int tmp = 0;
	BfmeOwnerDNB *owner = *(BfmeOwnerDNB **)((char *)this - 0xc);
	other->bfmeCallDNB(&owner->m_bfmeSub);
	return other;
}
