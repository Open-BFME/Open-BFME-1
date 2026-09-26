extern double g_bfmeSubB3;

class BfmeHostFF
{
public:
	void bfmeSetFrameFF(int frame);

	unsigned char m_bfmeHeadFF[8];
	unsigned char m_bfmeDoneFF;
	unsigned char m_bfmeFlagFF;
	unsigned char m_bfmeGap0FF[6];
	int m_bfmeStartFF;
	int m_bfmeEndFF;
	unsigned char m_bfmeGap1FF[8];
	float m_bfmeRatioFF;
};

void BfmeHostFF::bfmeSetFrameFF(int frame)
{
	int a = m_bfmeStartFF;

	if (frame < a)
		return;

	int b = m_bfmeEndFF;

	if (frame > b)
		return;

	if (m_bfmeFlagFF && (frame == b || a == b))
	{
		m_bfmeRatioFF = 0.0f;
		m_bfmeDoneFF = 1;

		return;
	}

	if (!m_bfmeFlagFF && (frame == a || a == b))
	{
		m_bfmeDoneFF = 1;
		m_bfmeRatioFF = 1.0f;

		return;
	}

	m_bfmeRatioFF = (float)(g_bfmeSubB3 - (double)(frame - a) / (double)(b - a));
}
