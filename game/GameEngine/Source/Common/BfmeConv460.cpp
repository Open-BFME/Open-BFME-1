struct BfmePartBGD
{
	unsigned char m_bfmeHead[4];
};

class BfmeSinkBGD
{
public:
	void bfmeDoBGD(BfmePartBGD *one, BfmePartBGD *two);
};

class BfmeThingBGD
{
public:
	void bfmeGoBGD(BfmeSinkBGD *sink);
	unsigned char m_bfmeHead[0x24];
	BfmePartBGD m_bfmeA;
	unsigned char m_bfmeGap[0x24];
	BfmePartBGD m_bfmeB;
};

void BfmeThingBGD::bfmeGoBGD(BfmeSinkBGD *sink)
{
	sink->bfmeDoBGD(&m_bfmeA, &m_bfmeB);
}
