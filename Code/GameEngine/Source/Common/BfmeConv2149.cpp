class BfmeQueueXO
{
public:
	void bfmeAppendXO(int a, int b, int c, int d);
	void bfmeSendXO(int a, int b, int c, int d, int e, int f);
};

class BfmeHostXO
{
public:
	void bfmeFlushXO();

	BfmeQueueXO *m_bfme00XO;
	unsigned char m_bfmeHeadXO[0xb4 - 4];
	int m_bfmeB4XO;
	int m_bfmeB8XO;
	int m_bfmeBCXO;
	int m_bfmeC0XO;
	int m_bfmeAXO[2];
	unsigned int m_bfmeCXO[2];
	unsigned int m_bfmeBXO[2];
};

void BfmeHostXO::bfmeFlushXO()
{
	if (m_bfmeBCXO >= 0)
	{
		m_bfme00XO->bfmeAppendXO(m_bfmeB4XO, m_bfmeB8XO, m_bfmeBCXO, m_bfmeC0XO);

		m_bfmeBCXO = -1;
	}

	unsigned int i;

	for (i = 0; i < 2; i++)
	{
		int a = m_bfmeAXO[i];

		if (a < 0)
			continue;

		unsigned int b = m_bfmeBXO[i];

		if (b <= 0)
			continue;

		m_bfme00XO->bfmeSendXO(m_bfmeB4XO, m_bfmeB8XO, a, i, -(int)b, m_bfmeCXO[i]);

		m_bfmeAXO[i] = -1;
	}
}
