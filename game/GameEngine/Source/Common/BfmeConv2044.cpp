extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

class BfmeHostEX
{
public:
	void bfmeSetEX(float t);

	unsigned char m_bfmeHeadEX[0xe4];
	unsigned char m_bfmeFlagEX;
	unsigned char m_bfmeGapEX[3];
	int m_bfmeLoEX;
	int m_bfmeHiEX;
	int m_bfmeValEX;
	float m_bfmeTEX;
};

void BfmeHostEX::bfmeSetEX(float t)
{
	m_bfmeTEX = t;
	m_bfmeValEX = 0;

	if (m_bfmeFlagEX)
	{
		if (t <= BfmeZeroRange)
			m_bfmeValEX = m_bfmeLoEX;
		else if (t >= g_bfmeDefaultBU)
			m_bfmeValEX = m_bfmeHiEX;
		else
			m_bfmeValEX = (int)((m_bfmeHiEX - m_bfmeLoEX) * t + m_bfmeLoEX);
	}
}
