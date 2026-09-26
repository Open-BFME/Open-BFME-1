extern "C" unsigned char bfmeVftSF[];

class BfmeThingSF
{
public:
	void bfmeTailSF();
	void bfmeResetSF();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeOne;
	unsigned char m_bfmeGapTwo[0x20];
	void *m_bfmeTwo;
	void *m_bfmeThree;
};

void BfmeThingSF::bfmeResetSF()
{
	m_bfmeVft = bfmeVftSF;
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	m_bfmeThree = 0;
	bfmeTailSF();
}
