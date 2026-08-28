class BfmeOutCSE
{
public:
	virtual void bfmeSpareCSE_0();
	virtual void bfmeSpareCSE_1();
	virtual void bfmeSpareCSE_2();
	virtual void bfmeSpareCSE_3();
	virtual void bfmeSpareCSE_4();
	virtual void bfmeBeginCSE();
	virtual void bfmeSpareCSE_6();
	virtual void bfmeSpareCSE_7();
	virtual void bfmeSendCSE(int code);
	virtual void bfmeSpareCSE_9();
	virtual void bfmeSpareCSE_10();
	virtual void bfmeSpareCSE_11();
	virtual void bfmeSpareCSE_12();
	virtual void bfmeSpareCSE_13();
	virtual void bfmeWriteVCSE(void *what);
};

class BfmeSubCSE
{
public:
	bool bfmeAskCSE();
};

class BfmeThingCSE
{
public:
	unsigned char m_bfmeHead[8];
	BfmeSubCSE *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSE *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSE(void *one, void *two);
};

void BfmeThingCSE::bfmeGoCSE(void *one, void *two)
{
	if (m_bfmeSub->bfmeAskCSE())
	{
		m_bfmeOut->bfmeBeginCSE();
		m_bfmeVal = two;
		m_bfmeOut->bfmeWriteVCSE(one);
		m_bfmeOut->bfmeSendCSE(0x15);
	}
}
