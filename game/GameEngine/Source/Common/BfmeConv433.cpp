class BfmeEndBBA
{
public:
	void bfmeRunBBA();
};

struct BfmeGotBBA
{
	unsigned char m_bfmeHead[8];
	BfmeEndBBA *m_bfmeEnd;
};

class BfmeSubBBA
{
public:
	BfmeGotBBA *bfmeFindBBA();
};

class BfmeThingBBA
{
public:
	void bfmeGoBBA();
	BfmeSubBBA *m_bfmeSub;
};

void BfmeThingBBA::bfmeGoBBA()
{
	m_bfmeSub->bfmeFindBBA()->m_bfmeEnd->bfmeRunBBA();
}
