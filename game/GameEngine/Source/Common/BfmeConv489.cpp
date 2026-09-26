class BfmeThingBMB
{
public:
	void bfmeStepBMB();
	void bfmeGoBMB();
	unsigned char m_bfmeHead[0x1a0];
	int m_bfmeCount;
};

void BfmeThingBMB::bfmeGoBMB()
{
	if (m_bfmeCount == 0)
		bfmeStepBMB();
	++m_bfmeCount;
}
