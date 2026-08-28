struct BfmeSubBSF
{
	void bfmeSetBSF(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBSF
{
public:
	BfmeThingBSF *bfmeGoBSF(unsigned short *src, void *what);
	unsigned short m_bfmeKey;
	unsigned char m_bfmePad[2];
	BfmeSubBSF m_bfmeSub;
};

BfmeThingBSF *BfmeThingBSF::bfmeGoBSF(unsigned short *src, void *what)
{
	m_bfmeKey = *src;
	m_bfmeSub.bfmeSetBSF(what);
	return this;
}
