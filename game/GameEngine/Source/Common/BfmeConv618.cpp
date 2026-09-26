class BfmeTwoCKF
{
public:
	virtual void bfmeSpareCKF0();
	virtual void bfmeSpareCKF1();
	virtual void bfmeSpareCKF2();
	virtual void bfmeSpareCKF3();
	virtual void bfmeSpareCKF4();
	virtual void bfmeSpareCKF5();
	virtual void bfmeSpareCKF6();
	virtual void bfmeRunCKF(void *value, void *buf);
};

class BfmeOneCKF
{
public:
	BfmeTwoCKF *bfmeTwoCKF();
};

class BfmeSubCKF
{
public:
	BfmeOneCKF *bfmeOneCKF();
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeVal;
};

class BfmeThingCKF
{
public:
	int bfmeTailCKF();
	int bfmeGoCKF();
	unsigned char m_bfmeHead[0x1c];
	BfmeSubCKF *m_bfmeSub;
	unsigned char m_bfmeGap[4];
	unsigned char m_bfmeBuf[4];
};

int BfmeThingCKF::bfmeGoCKF()
{
	BfmeOneCKF *one = m_bfmeSub->bfmeOneCKF();
	if (one == 0)
		return -2;
	BfmeTwoCKF *two = one->bfmeTwoCKF();
	if (two == 0)
		return -2;
	two->bfmeRunCKF(m_bfmeSub->m_bfmeVal, m_bfmeBuf);
	return bfmeTailCKF();
}
