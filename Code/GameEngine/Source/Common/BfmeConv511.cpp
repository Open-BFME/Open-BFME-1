class BfmeThingBQA
{
public:
	void bfmeStepBQA();
	int bfmeGoBQA();
	unsigned char m_bfmeHead[0x24];
	int *m_bfmeBegin;
	int *m_bfmeEnd;
	unsigned char m_bfmeGap[4];
	bool m_bfmeReady;
};

int BfmeThingBQA::bfmeGoBQA()
{
	if (!m_bfmeReady)
	{
		bfmeStepBQA();
		m_bfmeReady = true;
	}
	return m_bfmeEnd - m_bfmeBegin;
}
