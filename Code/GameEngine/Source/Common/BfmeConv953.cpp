// Open-BFME5 conversions.

class BfmeRank953
{
public:
	int bfmeRank953() const;
private:
	int m_bfmeGap[6];
	float m_bfmeLevel;
	int m_bfmeGap2;
	float m_bfmeScale;
	float m_bfmeLow;
	float m_bfmeHigh;
};

int BfmeRank953::bfmeRank953() const
{
	if (m_bfmeLevel == 0.0f)
		return 3;
	if (m_bfmeHigh * m_bfmeScale >= m_bfmeLevel)
		return 2;
	if (m_bfmeLow * m_bfmeScale >= m_bfmeLevel)
		return 1;
	return 0;
}
