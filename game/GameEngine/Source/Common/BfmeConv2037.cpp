extern float g_bfmeDefaultBU;

class BfmeKeyEN
{
public:
	unsigned int m_bfmeTimeEN;
	float m_bfmeXEN;
	float m_bfmeYEN;
	float m_bfmeZEN;
};

class BfmeHostEN
{
public:
	void bfmeStepEN();

	unsigned char m_bfmeHeadEN[0xc];
	BfmeKeyEN m_bfmeKeysEN[8];
	unsigned char m_bfmePadEN[8];
	float m_bfmePxEN;
	float m_bfmePyEN;
	float m_bfmePzEN;
	float m_bfmeVxEN;
	float m_bfmeVyEN;
	float m_bfmeVzEN;
	int m_bfmeIndexEN;
};

void BfmeHostEN::bfmeStepEN()
{
	int i = m_bfmeIndexEN;
	unsigned int dt = m_bfmeKeysEN[i + 1].m_bfmeTimeEN;

	if (dt == 0)
	{
		m_bfmeVxEN = 0.0f;
		m_bfmeVyEN = 0.0f;
		m_bfmeVzEN = 0.0f;
		return;
	}

	dt -= m_bfmeKeysEN[i].m_bfmeTimeEN;

	float inv = g_bfmeDefaultBU / (float)dt;

	m_bfmeVxEN = (m_bfmeKeysEN[i].m_bfmeXEN - m_bfmePxEN) * inv;
	m_bfmeVyEN = (m_bfmeKeysEN[i].m_bfmeYEN - m_bfmePyEN) * inv;
	m_bfmeVzEN = (m_bfmeKeysEN[i].m_bfmeZEN - m_bfmePzEN) * inv;
}
