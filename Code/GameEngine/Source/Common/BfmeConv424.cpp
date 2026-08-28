void bfmeSendATB(int what);

class BfmeThingATB
{
public:
	void bfmeGoATB();
	unsigned char m_bfmeHead[8];
	void *m_bfmeWhat;
	bool m_bfmeReady;
	bool m_bfmeDone;
};

void BfmeThingATB::bfmeGoATB()
{
	if (m_bfmeWhat != 0 && !m_bfmeDone)
	{
		if (m_bfmeReady)
		{
			bfmeSendATB(0);
			m_bfmeDone = true;
			return;
		}
		m_bfmeWhat = 0;
	}
}
