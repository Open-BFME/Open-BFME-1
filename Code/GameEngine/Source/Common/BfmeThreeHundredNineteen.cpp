struct BfmeLimitRS
{
	unsigned char m_bfmeHead[0x3c];
	unsigned int m_bfmeCap;
};

extern BfmeLimitRS *g_bfmeLimitRS;

class BfmeThingRS
{
public:
	void bfmeDropRS(int what);
	void bfmeTrimRS();
	unsigned char m_bfmeHead[0x338];
	unsigned int m_bfmeAt;
};

void BfmeThingRS::bfmeTrimRS()
{
	unsigned int at = m_bfmeAt;
	if (at > 0 && g_bfmeLimitRS->m_bfmeCap > at)
	{
		bfmeDropRS(0x49);
		m_bfmeAt = 0;
	}
}
