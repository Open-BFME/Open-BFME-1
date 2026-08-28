class BfmeSubBEB
{
public:
	bool bfmeAskBEB();
};

class BfmeThingBEB
{
public:
	bool bfmeGoBEB();
	unsigned char m_bfmeHead[0x1e8];
	BfmeSubBEB *m_bfmeSub;
};

bool BfmeThingBEB::bfmeGoBEB()
{
	BfmeSubBEB *sub = m_bfmeSub;
	if (sub == 0)
		return false;
	return sub->bfmeAskBEB();
}
