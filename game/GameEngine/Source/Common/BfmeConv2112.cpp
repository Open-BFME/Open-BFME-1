class BfmeSinkZT
{
public:
	void bfmeNotifyZT(bool flag);
};

class BfmeHostZT
{
public:
	void bfmeAdvanceZT(int delta);

	int m_bfmeHeadZT;
	int m_bfmeLimitZT;
	int m_bfmeValueZT;
	BfmeSinkZT *m_bfmeSinkZT;
};

void BfmeHostZT::bfmeAdvanceZT(int delta)
{
	m_bfmeValueZT = m_bfmeValueZT + delta;

	if (m_bfmeSinkZT != 0)
		m_bfmeSinkZT->bfmeNotifyZT(m_bfmeLimitZT < m_bfmeValueZT);
}
