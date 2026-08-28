class BfmeOutCSH
{
public:
	virtual void bfmeSpareCSH_0();
	virtual void bfmeSpareCSH_1();
	virtual void bfmeSpareCSH_2();
	virtual void bfmeSpareCSH_3();
	virtual void bfmeSpareCSH_4();
	virtual void bfmeBeginCSH();
	virtual void bfmeSpareCSH_6();
	virtual void bfmeSpareCSH_7();
	virtual void bfmeSendCSH(int code);
	virtual void bfmeSpareCSH_9();
	virtual void bfmeSpareCSH_10();
	virtual void bfmeSpareCSH_11();
	virtual void bfmeSpareCSH_12();
	virtual void bfmeSpareCSH_13();
	virtual void bfmeSpareCSH_14();
	void bfmeWriteNCSH(void *what);
};

class BfmeSubCSH
{
public:
	bool bfmeAskCSH();
};

class BfmeThingCSH
{
public:
	unsigned char m_bfmeHead[8];
	BfmeSubCSH *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSH *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSH(void *one, void *two);
};

void BfmeThingCSH::bfmeGoCSH(void *one, void *two)
{
	if (m_bfmeSub->bfmeAskCSH())
	{
		m_bfmeOut->bfmeBeginCSH();
		m_bfmeVal = two;
		m_bfmeOut->bfmeWriteNCSH(one);
		m_bfmeOut->bfmeSendCSH(0x13);
	}
}
