class BfmeSubDSN
{
public:
	void bfmeOneDSN(void *what);
	void bfmeTwoDSN(void *what);
};

struct BfmeOwnerDSN
{
	unsigned char m_bfmeHead[0x5c];
	BfmeSubDSN m_bfmeSub;
};

struct BfmeThingDSN
{
	void bfmeGoDSN();
	void bfmeGoDSO();
};

void BfmeThingDSN::bfmeGoDSN()
{
	void *what = *(void **)((char *)this - 0xd8);
	BfmeOwnerDSN *owner = *(BfmeOwnerDSN **)((char *)this - 0xdc);
	owner->m_bfmeSub.bfmeOneDSN(what);
}

void BfmeThingDSN::bfmeGoDSO()
{
	void *what = *(void **)((char *)this - 0xd8);
	BfmeOwnerDSN *owner = *(BfmeOwnerDSN **)((char *)this - 0xdc);
	owner->m_bfmeSub.bfmeTwoDSN(what);
}
