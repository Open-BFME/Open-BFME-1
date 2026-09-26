struct BfmeGotBHF
{
	unsigned char m_bfmeHead[0x48];
	int m_bfmeValue;
};

class BfmeSubBHF
{
public:
	BfmeGotBHF *bfmeFindBHF();
};

int bfmeGoBHF(BfmeSubBHF *sub)
{
	if (sub == 0)
		return -1;
	return sub->bfmeFindBHF()->m_bfmeValue;
}
