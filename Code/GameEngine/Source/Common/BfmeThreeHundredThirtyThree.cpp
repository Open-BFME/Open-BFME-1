extern "C" unsigned char bfmeVftSE[];

class BfmeThingSE
{
public:
	void bfmeTailSE();
	void bfmeResetSE();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeOne;
	unsigned char m_bfmeGapTwo[0x24];
	void *m_bfmeTwo;
};

void BfmeThingSE::bfmeResetSE()
{
	m_bfmeVft = bfmeVftSE;
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	bfmeTailSE();
}
