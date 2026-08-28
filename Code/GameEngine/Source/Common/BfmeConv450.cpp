class BfmeThingBEE
{
public:
	bool bfmeAskBEE();
	bool bfmeGoBEE();
	unsigned char m_bfmeHead[0x3e0];
	bool m_bfmeFlag;
};

bool BfmeThingBEE::bfmeGoBEE()
{
	if (m_bfmeFlag)
		return false;
	return bfmeAskBEE();
}
