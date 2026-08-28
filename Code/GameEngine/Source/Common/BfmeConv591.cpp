class BfmeOuterCFD
{
public:
	void bfmeOneCFD();
	void bfmeTwoCFD();
};

class BfmeThingCFD
{
public:
	int bfmeGoCFD();
	unsigned char m_bfmeHead[0x20];
	bool m_bfmeFlag;
};

int BfmeThingCFD::bfmeGoCFD()
{
	BfmeOuterCFD *outer = (BfmeOuterCFD *)((char *)this - 0x10);
	if (!m_bfmeFlag)
	{
		outer->bfmeOneCFD();
		m_bfmeFlag = true;
		return 5;
	}
	outer->bfmeTwoCFD();
	return 5;
}
