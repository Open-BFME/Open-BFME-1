struct BfmeSubCBD
{
	unsigned char m_bfmeHead[0x18];
	int m_bfmeVal;
	unsigned int m_bfmeFlags;
};

class BfmeThingCBD
{
public:
	void bfmeStepCBD(int value);
	unsigned char m_bfmeHead[0x50];
	BfmeSubCBD *m_bfmeSub;
};

extern int bfmeTheCBD;

int bfmeGoCBD(BfmeThingCBD *what)
{
	what->bfmeStepCBD(what->m_bfmeSub->m_bfmeVal - 1);
	what->m_bfmeSub->m_bfmeFlags &= 0xFDFFFFFFu;
	return bfmeTheCBD;
}
