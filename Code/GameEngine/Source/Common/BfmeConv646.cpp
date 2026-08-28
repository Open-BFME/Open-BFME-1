class BfmeOutCTC
{
public:
	virtual void bfmeSpareCTC_0();
	virtual void bfmeSpareCTC_1();
	virtual void bfmeSpareCTC_2();
	virtual void bfmeSpareCTC_3();
	virtual void bfmeSpareCTC_4();
	virtual void bfmeBeginCTC();
	virtual void bfmeSpareCTC_6();
	virtual void bfmeSpareCTC_7();
	virtual void bfmeSendCTC(int code);
	virtual void bfmeSpareCTC_9();
	virtual void bfmeSpareCTC_10();
	virtual void bfmeSpareCTC_11();
	virtual void bfmeSpareCTC_12();
	virtual void bfmeSpareCTC_13();
	virtual void bfmeWriteVCTC(void *what);
};

class BfmeSubCTC
{
public:
	bool bfmeAskCTC();
};

class BfmeThingCTC
{
public:
	void bfmeGoCTC(void *one, void *two);
	unsigned char m_bfmeHead[8];
	BfmeSubCTC *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCTC *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	unsigned char m_bfmeGap3[0x120];
	int m_bfmeA;
	unsigned char m_bfmeGap4[0x1b5];
	bool m_bfmeB;
	bool m_bfmeC;
};

void BfmeThingCTC::bfmeGoCTC(void *one, void *two)
{
	if (m_bfmeSub->bfmeAskCTC())
	{
		m_bfmeOut->bfmeBeginCTC();
		m_bfmeOut->bfmeWriteVCTC(one);
		m_bfmeVal = two;
		m_bfmeA = 0;
		m_bfmeB = false;
		m_bfmeC = false;
		m_bfmeOut->bfmeSendCTC(0x24);
	}
}
