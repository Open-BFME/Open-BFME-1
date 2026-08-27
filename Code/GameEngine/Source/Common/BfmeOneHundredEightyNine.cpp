// Settings written down before the work is asked for, and a held thing let go
// of.

class BfmeThingDY
{
public:
	virtual void bfmeSpare000DY(void) = 0;
	virtual void bfmeSpare001DY(void) = 0;
	virtual void bfmeSpare002DY(void) = 0;
	virtual void bfmeDoDY(void) = 0;

	void bfmeSetDY(int what, int how);

private:
	unsigned char m_bfmeHead[0x20];		// 0x04
	int m_bfmeFirst;			// 0x24
	unsigned char m_bfmeGap[4];		// 0x28
	int m_bfmeWhat;				// 0x2c
	int m_bfmeNone;				// 0x30
	unsigned char m_bfmeSpare[0x10];	// 0x34
	int m_bfmeSecond;			// 0x44
	int m_bfmeHow;				// 0x48
};

void BfmeThingDY::bfmeSetDY(int what, int how)
{
	m_bfmeFirst = 1;
	m_bfmeSecond = 1;
	m_bfmeHow = how;
	m_bfmeWhat = what;
	m_bfmeNone = 0;

	bfmeDoDY();
}


class BfmeCountedDT
{
public:
	virtual void bfmeGoneDT(void) = 0;
	virtual void bfmeSpare001DT(void) = 0;
	virtual void bfmeSpare002DT(void) = 0;
	virtual void bfmeSpare003DT(void) = 0;
	virtual void bfmeSpare004DT(void) = 0;
	virtual void bfmeSpare005DT(void) = 0;
	virtual void bfmeSpare006DT(void) = 0;
	virtual void bfmeSpare007DT(void) = 0;
	virtual void bfmeSpare008DT(void) = 0;
	virtual void bfmeSpare009DT(void) = 0;
	virtual void bfmeSpare010DT(void) = 0;
	virtual void bfmeSpare011DT(void) = 0;
	virtual void bfmeSpare012DT(void) = 0;
	virtual void bfmeSpare013DT(void) = 0;
	virtual void bfmeSpare014DT(void) = 0;
	virtual void bfmeSpare015DT(void) = 0;
	virtual void bfmeStopDT(void) = 0;

	int m_bfmeCount;			// 0x4
};

void __stdcall bfmeDropDT(BfmeCountedDT **slot)
{
	BfmeCountedDT *held = *slot;

	if (held != 0)
	{
		held->bfmeStopDT();

		if (--held->m_bfmeCount == 0)
			held->bfmeGoneDT();

		*slot = 0;
	}
}
