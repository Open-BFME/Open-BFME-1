class BfmeThingDSA
{
public:
	void *bfmeGoDSA(void *what);
	void *bfmeTailDSA(void *what);
	char m_bfmeHead[0x40];
	char m_bfmeFlag;
};

void *BfmeThingDSA::bfmeGoDSA(void *what)
{
	if (m_bfmeFlag)
		return 0;
	return bfmeTailDSA(what);
}
