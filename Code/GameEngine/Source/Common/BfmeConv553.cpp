class BfmeThingBXF
{
public:
	void bfmeOnceBXF();
	void bfmeThenBXF(int value);
	void bfmeGoBXF();
	unsigned char m_bfmeHead[0x3ac];
	bool m_bfmeFlag;
};

void BfmeThingBXF::bfmeGoBXF()
{
	if (!m_bfmeFlag)
	{
		m_bfmeFlag = true;
		bfmeOnceBXF();
	}
	bfmeThenBXF(0);
}
