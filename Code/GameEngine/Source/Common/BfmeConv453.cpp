class BfmeSubBFD
{
public:
	bool bfmeAskBFD();
};

class BfmeThingBFD
{
public:
	int bfmeGoBFD();
	unsigned char m_bfmeHead[0x28];
	BfmeSubBFD *m_bfmeSub;
};

int BfmeThingBFD::bfmeGoBFD()
{
	BfmeSubBFD *sub = m_bfmeSub;
	if (sub != 0)
		return sub->bfmeAskBFD();
	return 0;
}
