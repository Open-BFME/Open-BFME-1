class BfmeOutCSA
{
public:
	virtual void bfmeSpareCSA_0();
	virtual void bfmeSpareCSA_1();
	virtual void bfmeSpareCSA_2();
	virtual void bfmeSpareCSA_3();
	virtual void bfmeSpareCSA_4();
	virtual void bfmeBeginCSA();
	virtual void bfmeSpareCSA_6();
	virtual void bfmeSpareCSA_7();
	virtual void bfmeSendCSA(int code);
	virtual void bfmeSpareCSA_9();
	virtual void bfmeSpareCSA_10();
	virtual void bfmeSpareCSA_11();
	virtual void bfmeSpareCSA_12();
	virtual void bfmeSpareCSA_13();
	virtual void bfmeWriteVCSA(void *what);
};

class BfmeSubCSA
{
public:
	bool bfmeAskCSA();
};

class BfmeThingCSA
{
public:
	unsigned char m_bfmeHead[8];
	BfmeSubCSA *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSA *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSA(void *what);
};

void BfmeThingCSA::bfmeGoCSA(void *what)
{
	if (m_bfmeSub->bfmeAskCSA())
	{
		m_bfmeOut->bfmeBeginCSA();
		m_bfmeVal = what;
		m_bfmeOut->bfmeSendCSA(0x29);
	}
}
