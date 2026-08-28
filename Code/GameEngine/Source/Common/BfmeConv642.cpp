class BfmeOutCSG
{
public:
	virtual void bfmeSpareCSG_0();
	virtual void bfmeSpareCSG_1();
	virtual void bfmeSpareCSG_2();
	virtual void bfmeSpareCSG_3();
	virtual void bfmeSpareCSG_4();
	virtual void bfmeBeginCSG();
	virtual void bfmeSpareCSG_6();
	virtual void bfmeSpareCSG_7();
	virtual void bfmeSendCSG(int code);
	virtual void bfmeSpareCSG_9();
	virtual void bfmeSpareCSG_10();
	virtual void bfmeSpareCSG_11();
	virtual void bfmeSpareCSG_12();
	virtual void bfmeSpareCSG_13();
	virtual void bfmeSpareCSG_14();
	void bfmeWriteNCSG(void *what);
};

class BfmeSubCSG
{
public:
	bool bfmeAskCSG();
};

class BfmeThingCSG
{
public:
	unsigned char m_bfmeHead[8];
	BfmeSubCSG *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSG *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSG(void *one, void *two);
};

void BfmeThingCSG::bfmeGoCSG(void *one, void *two)
{
	if (m_bfmeSub->bfmeAskCSG())
	{
		m_bfmeOut->bfmeBeginCSG();
		m_bfmeVal = two;
		m_bfmeOut->bfmeWriteNCSG(one);
		m_bfmeOut->bfmeSendCSG(0x12);
	}
}
