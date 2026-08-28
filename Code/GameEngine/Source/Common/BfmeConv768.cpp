class BfmeThingDSB
{
public:
	bool bfmeGoDSB();
	bool bfmeTailDSB();
	char m_bfmeHead[0xf8];
	char m_bfmeFlag;
};

bool BfmeThingDSB::bfmeGoDSB()
{
	if (m_bfmeFlag)
		return false;
	return bfmeTailDSB();
}
