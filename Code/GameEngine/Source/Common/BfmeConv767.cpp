class BfmeSubDRE
{
public:
	void *bfmeOneDRE(void *what);
};

class BfmeOtherDRE
{
public:
	void bfmeTwoDRE(void *value);
};

class BfmeThingDRE
{
public:
	BfmeOtherDRE *bfmeGoDRE(BfmeOtherDRE *other, void *what);
	unsigned char m_bfmeHead[0x170];
	BfmeSubDRE m_bfmeSub;
};

BfmeOtherDRE *BfmeThingDRE::bfmeGoDRE(BfmeOtherDRE *other, void *what)
{
	volatile int tmp = 0;
	void *r = m_bfmeSub.bfmeOneDRE(what);
	other->bfmeTwoDRE(r);
	return other;
}
