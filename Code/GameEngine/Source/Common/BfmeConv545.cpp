extern "C" unsigned char bfmeVftBWD[];

class BfmeSubBWD
{
public:
	void bfmeInitSubBWD();
};

struct BfmeThingBWD
{
	BfmeThingBWD *bfmeInitBWD();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[4];
	BfmeSubBWD m_bfmeSub;
	unsigned char m_bfmeTail[0x67];
	bool m_bfmeA;
	bool m_bfmeB;
	unsigned char m_bfmePad[2];
	int m_bfmeNum;
};

BfmeThingBWD *BfmeThingBWD::bfmeInitBWD()
{
	m_bfmeSub.bfmeInitSubBWD();
	m_bfmeA = false;
	m_bfmeB = false;
	m_bfmeVft = bfmeVftBWD;
	m_bfmeNum = 3;
	return this;
}
