class BfmeThingBGG
{
public:
	void bfmeStepBGG();
	void bfmeGoBGG();
	unsigned char m_bfmeHead[0x38];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[7];
	bool m_bfmeFlag;
};

void BfmeThingBGG::bfmeGoBGG()
{
	bfmeStepBGG();
	if (m_bfmeWhat != 0)
		m_bfmeFlag = true;
}
