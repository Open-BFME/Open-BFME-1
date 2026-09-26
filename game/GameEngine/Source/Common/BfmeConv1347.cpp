// Open-BFME5 conversions.

struct BfmeHandleUZA
{
	int m_bfmeValue;
};

class BfmeSubAUZA
{
public:
	BfmeHandleUZA bfmeGetAUZA(int a, int b) const;
};

class BfmeSubBUZA
{
public:
	BfmeHandleUZA bfmeGetBUZA(int a, int b) const;
};

class BfmeThingAUZA
{
public:
	BfmeHandleUZA bfmeGoAUZA(int a, int b) const;
	char m_bfmePad[0x9c];
	BfmeSubAUZA *m_bfmeSub;
};

BfmeHandleUZA BfmeThingAUZA::bfmeGoAUZA(int a, int b) const
{
	volatile int m_bfmeDead = 0;
	return m_bfmeSub->bfmeGetAUZA(a, b);
}

class BfmeThingBUZA
{
public:
	BfmeHandleUZA bfmeGoBUZA(int a, int b) const;
	char m_bfmePad[0x9c];
	BfmeSubBUZA *m_bfmeSub;
};

BfmeHandleUZA BfmeThingBUZA::bfmeGoBUZA(int a, int b) const
{
	volatile int m_bfmeDead = 0;
	return m_bfmeSub->bfmeGetBUZA(a, b);
}
