class BfmeSubDST
{
public:
	void **bfmeOneDST(void **what);
};

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **what);
};

struct BfmeThingDST
{
	void bfmeGoDST(void *what, void *v);
	unsigned char m_bfmeHead[0x340];
	BfmeSubDST m_bfmeSub;
};

void BfmeThingDST::bfmeGoDST(void *what, void *v)
{
	*m_bfmeSub.bfmeOneDST(&what) = v;
}

struct BfmeThingDSU
{
	void bfmeGoDSU(void *what, void *v);
	unsigned char m_bfmeHead[0x120];
	BfmeSubDSU m_bfmeSub;
};

void BfmeThingDSU::bfmeGoDSU(void *what, void *v)
{
	*m_bfmeSub.bfmeTwoDSU(&what) = v;
}
