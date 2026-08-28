class BfmeThingCED
{
public:
	bool bfmeOneCED();
	bool bfmeTwoCED();
	bool bfmeThreeCED();
	void bfmeGoCED();
	unsigned char m_bfmeHead[0x54];
	bool m_bfmeFlag;
};

void BfmeThingCED::bfmeGoCED()
{
	if (bfmeOneCED() && bfmeTwoCED() && bfmeThreeCED())
		m_bfmeFlag = true;
}
