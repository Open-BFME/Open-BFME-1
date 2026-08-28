extern "C" unsigned char bfmeVftSG[];

class BfmeThingSG
{
public:
	void bfmeTailSG();
	void bfmeResetSG();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeOne;
	unsigned char m_bfmeGapTwo[0x20];
	void *m_bfmeTwo;
};

void BfmeThingSG::bfmeResetSG()
{
	m_bfmeVft = bfmeVftSG;
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	bfmeTailSG();
}
