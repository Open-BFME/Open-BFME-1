struct BfmeBlockZC
{
	int m_bfmeWords[20];
};

class BfmeThingZC
{
public:
	void bfmeTailZC();
	void bfmeGoZC();
	unsigned char m_bfmeHead[0x100];
	BfmeBlockZC m_bfmeCur;
	BfmeBlockZC m_bfmeB;
	BfmeBlockZC m_bfmeA;
	unsigned char m_bfmeGap[0xfc];
	int m_bfmeMode;
};

void BfmeThingZC::bfmeGoZC()
{
	int mode = m_bfmeMode;
	if (mode >= 0)
	{
		if (mode > 1)
		{
			if (mode == 2)
				m_bfmeCur = m_bfmeB;
		}
		else
		{
			m_bfmeCur = m_bfmeA;
		}
	}
	bfmeTailZC();
}
