class BfmeSubBNC
{
public:
	void bfmeDoBNC(void *one, void *two);
};

struct BfmeOwnerBNC
{
	unsigned char m_bfmeHead[0x34];
	BfmeSubBNC *m_bfmeSub;
};

void bfmeGoBNC(BfmeOwnerBNC *owner, void *one, void *two)
{
	BfmeSubBNC *sub = owner->m_bfmeSub;
	if (sub != 0)
		sub->bfmeDoBNC(one, two);
}
