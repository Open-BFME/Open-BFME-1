struct BfmeLimitRN
{
	unsigned char m_bfmeHead[0x3c];
	unsigned int m_bfmeCap;
};

extern BfmeLimitRN *g_bfmeLimitRN;

class BfmeThingRN
{
public:
	void bfmeDropRN(int what);
	void bfmeTrimRN();
	unsigned char m_bfmeHead[0x33c];
	unsigned int m_bfmeAt;
};

void BfmeThingRN::bfmeTrimRN()
{
	unsigned int at = m_bfmeAt;
	if (at > 0 && g_bfmeLimitRN->m_bfmeCap > at)
	{
		bfmeDropRN(4);
		m_bfmeAt = 0;
	}
}
