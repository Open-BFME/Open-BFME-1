class BfmeOutCSD
{
public:
	virtual void bfmeSpareCSD_0();
	virtual void bfmeSpareCSD_1();
	virtual void bfmeSpareCSD_2();
	virtual void bfmeSpareCSD_3();
	virtual void bfmeSpareCSD_4();
	virtual void bfmeBeginCSD();
	virtual void bfmeSpareCSD_6();
	virtual void bfmeSpareCSD_7();
	virtual void bfmeSendCSD(int code);
	virtual void bfmeSpareCSD_9();
	virtual void bfmeSpareCSD_10();
	virtual void bfmeSpareCSD_11();
	virtual void bfmeSpareCSD_12();
	virtual void bfmeSpareCSD_13();
	virtual void bfmeWriteVCSD(void *what);
};

class BfmeSubCSD
{
public:
	bool bfmeAskCSD();
};

class BfmeThingCSD
{
public:
	unsigned char m_bfmeHead[8];
	BfmeSubCSD *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSD *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSD(void *one, void *two);
};

void BfmeThingCSD::bfmeGoCSD(void *one, void *two)
{
	if (m_bfmeSub->bfmeAskCSD())
	{
		m_bfmeOut->bfmeBeginCSD();
		m_bfmeVal = two;
		m_bfmeOut->bfmeWriteVCSD(one);
		m_bfmeOut->bfmeSendCSD(0x14);
	}
}
