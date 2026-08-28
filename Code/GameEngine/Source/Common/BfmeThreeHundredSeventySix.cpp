struct BfmeClockYD
{
	unsigned char m_bfmeHead[0x3c];
	int m_bfmeNow;
};

extern BfmeClockYD *g_bfmeClockYD;

class BfmeThingYD
{
public:
	virtual void bfmeSpareYDa0();
	virtual void bfmeSpareYDa1();
	virtual void bfmeSpareYDa2();
	virtual void bfmeSpareYDa3();
	virtual void bfmeSpareYDa4();
	virtual void bfmeSpareYDa5();
	virtual bool bfmeAskTwoYD();
	virtual void bfmeSpareYDb0();
	virtual void bfmeSpareYDb1();
	virtual void bfmeSpareYDb2();
	virtual bool bfmeAskOneYD();
	void bfmeStepYD();
	void bfmeSetYD(int what);
	void bfmeGoYD();
	unsigned char m_bfmeHead[0x2c];
	bool m_bfmeFlag;
	unsigned char m_bfmeGapOne[3];
	int m_bfmeCount;
	unsigned char m_bfmeGapTwo[4];
	int m_bfmeStamp;
};

void BfmeThingYD::bfmeGoYD()
{
	if (!bfmeAskOneYD())
		return;
	if (!bfmeAskTwoYD())
		return;
	bfmeStepYD();
	bfmeSetYD(2);
	m_bfmeFlag = false;
	m_bfmeCount = 0;
	m_bfmeStamp = g_bfmeClockYD->m_bfmeNow;
}
