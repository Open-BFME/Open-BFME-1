class BfmeTwoCKE
{
public:
	virtual void bfmeSpareCKE0();
	virtual void bfmeSpareCKE1();
	virtual void bfmeSpareCKE2();
	virtual void bfmeSpareCKE3();
	virtual void bfmeSpareCKE4();
	virtual void bfmeRunCKE(void *value, void *buf);
};

class BfmeOneCKE
{
public:
	BfmeTwoCKE *bfmeTwoCKE();
};

class BfmeSubCKE
{
public:
	BfmeOneCKE *bfmeOneCKE();
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeVal;
};

class BfmeThingCKE
{
public:
	int bfmeTailCKE();
	int bfmeGoCKE();
	unsigned char m_bfmeHead[0x1c];
	BfmeSubCKE *m_bfmeSub;
	unsigned char m_bfmeGap[4];
	unsigned char m_bfmeBuf[4];
};

int BfmeThingCKE::bfmeGoCKE()
{
	BfmeOneCKE *one = m_bfmeSub->bfmeOneCKE();
	if (one == 0)
		return -2;
	BfmeTwoCKE *two = one->bfmeTwoCKE();
	if (two == 0)
		return -2;
	two->bfmeRunCKE(m_bfmeSub->m_bfmeVal, m_bfmeBuf);
	return bfmeTailCKE();
}
