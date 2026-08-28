struct BfmeSubCBC
{
	unsigned char m_bfmeHead[0x18];
	int m_bfmeVal;
	unsigned int m_bfmeFlags;
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int value);
	unsigned char m_bfmeHead[0x50];
	BfmeSubCBC *m_bfmeSub;
};

extern int bfmeTheCBC;

int bfmeGoCBC(BfmeThingCBC *what)
{
	what->bfmeStepCBC(what->m_bfmeSub->m_bfmeVal + 1);
	what->m_bfmeSub->m_bfmeFlags &= 0xFDFFFFFFu;
	return bfmeTheCBC;
}
