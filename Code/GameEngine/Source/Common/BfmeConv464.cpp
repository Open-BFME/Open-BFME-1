class BfmeSubBHE
{
public:
	void bfmeDoBHE();
};

struct BfmeOwnerBHE
{
	unsigned char m_bfmeHead[0x210];
	BfmeSubBHE *m_bfmeSub;
};

int bfmeGoBHE(BfmeOwnerBHE *owner)
{
	owner->m_bfmeSub->bfmeDoBHE();
	return 1;
}
