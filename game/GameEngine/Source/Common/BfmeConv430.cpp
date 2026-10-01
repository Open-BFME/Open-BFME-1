struct BfmeClockAZA
{
	unsigned char m_bfmeHead[0x3c];
	int m_bfmeNow;
};

// Retail 0x012F0898 is EA's game-logic singleton, whose one canonical
// spelling is ?TheGameLogic@@3PAVGameLogic@@A.  BfmeClockAZA above is this TU's
// own view of that address, so the stamp read below casts at the use.
class GameLogic;

extern GameLogic *TheGameLogic;

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
	m_bfmeStamp = ((BfmeClockAZA *)TheGameLogic)->m_bfmeNow;
}
