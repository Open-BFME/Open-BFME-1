struct BfmeClockAZA
{
	unsigned char m_bfmeHead[0x3c];
	int m_bfmeNow;
};

extern BfmeClockAZA *g_bfmeClockAZA;

class BfmeThingAZA
{
public:
	virtual void bfmeSpareAZAa0();
	virtual void bfmeSpareAZAa1();
	virtual void bfmeSpareAZAa2();
	virtual void bfmeSpareAZAa3();
	virtual void bfmeSpareAZAa4();
	virtual void bfmeSpareAZAa5();
	virtual bool bfmeAskTwoAZA();
	virtual void bfmeSpareAZAb0();
	virtual void bfmeSpareAZAb1();
	virtual void bfmeSpareAZAb2();
	virtual bool bfmeAskOneAZA();
	void bfmeStepAZA();
	void bfmeSetAZA(int what);
	void bfmeGoAZA();
	unsigned char m_bfmeHead[0x2c];
	bool m_bfmeFlag;
	unsigned char m_bfmeGapOne[3];
	int m_bfmeCount;
	unsigned char m_bfmeGapTwo[4];
	int m_bfmeStamp;
};

void BfmeThingAZA::bfmeGoAZA()
{
	if (!bfmeAskOneAZA())
		return;
	if (bfmeAskTwoAZA())
		return;
	bfmeStepAZA();
	bfmeSetAZA(0);
	m_bfmeFlag = false;
	m_bfmeCount = 0;
	m_bfmeStamp = g_bfmeClockAZA->m_bfmeNow;
}
