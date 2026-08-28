extern "C" unsigned char bfmeVftTE[];

struct BfmeSubTE
{
	void bfmeStartTE();
	unsigned char m_bfmeHead[0x68];
};

class BfmeThingTE
{
public:
	BfmeThingTE *bfmeInitTE();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[4];
	BfmeSubTE m_bfmeSub;
	int m_bfmeOne;
	int m_bfmeTwo;
};

BfmeThingTE *BfmeThingTE::bfmeInitTE()
{
	m_bfmeSub.bfmeStartTE();
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	m_bfmeVft = bfmeVftTE;
	return this;
}
