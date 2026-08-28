class BfmeOwnerCGF
{
public:
	void bfmeOneCGF(void *what);
};

struct BfmeSubCGF
{
	unsigned char m_bfmeHead[4];
};

class BfmeThingCGF
{
public:
	void bfmeTwoCGF(void *what);
	void bfmeGoCGF(void *what);
	BfmeOwnerCGF *m_bfmeOwner;
	unsigned char m_bfmeGap[0xc];
	BfmeSubCGF m_bfmeSub;
};

void bfmeThreeCGF(void *what, BfmeSubCGF *sub);

void BfmeThingCGF::bfmeGoCGF(void *what)
{
	m_bfmeOwner->bfmeOneCGF(what);
	bfmeTwoCGF(what);
	bfmeThreeCGF(what, &m_bfmeSub);
}
