// Two errands: two charges wound up and their last readings kept, and a line of
// text put on the page with the place brought up to date.

class BfmeTargetFM
{
public:
	virtual void bfmeSpare000FM(void) = 0;
	virtual void bfmeSpare001FM(void) = 0;
	virtual void bfmeSpare002FM(void) = 0;
	virtual void bfmeSpare003FM(void) = 0;
	virtual void bfmeSpare004FM(void) = 0;
	virtual void bfmeSpare005FM(void) = 0;
	virtual void bfmeSpare006FM(void) = 0;
	virtual void bfmeSpare007FM(void) = 0;
	virtual void bfmeSpare008FM(void) = 0;
	virtual void bfmeSpare009FM(void) = 0;
	virtual void bfmeSpare010FM(void) = 0;
	virtual int bfmeAskFM(void) = 0;
	virtual void bfmeSpare012FM(void) = 0;
	virtual int bfmeGetFM(void) = 0;
};

class BfmeThingFM
{
public:
	void bfmeStopFM(void);

private:
	unsigned char m_bfmeHead[0xc];		// 0x00
	BfmeTargetFM *m_bfmeFirst;		// 0x0c
	int m_bfmeFirstGot;			// 0x10
	int m_bfmeFirstAsked;			// 0x14
	BfmeTargetFM *m_bfmeSecond;		// 0x18
	int m_bfmeSecondGot;			// 0x1c
	int m_bfmeSecondAsked;			// 0x20
};

void BfmeThingFM::bfmeStopFM(void)
{
	BfmeTargetFM *first = m_bfmeFirst;

	if (first == 0)
		return;

	m_bfmeFirstAsked = first->bfmeAskFM();
	m_bfmeFirstGot = m_bfmeFirst->bfmeGetFM();
	m_bfmeFirst = 0;

	BfmeTargetFM *second = m_bfmeSecond;

	if (second != 0)
	{
		m_bfmeSecondAsked = second->bfmeAskFM();
		m_bfmeSecondGot = m_bfmeSecond->bfmeGetFM();
		m_bfmeSecond = 0;

		return;
	}

	m_bfmeSecondAsked = 0;
	m_bfmeSecondGot = 0;
}


class BfmeThingFP
{
public:
	virtual void bfmeSpare000FP(void) = 0;
	virtual void bfmeSpare001FP(void) = 0;
	virtual void bfmeSpare002FP(void) = 0;
	virtual void bfmeSpare003FP(void) = 0;
	virtual void bfmeSpare004FP(void) = 0;
	virtual void bfmeSpare005FP(void) = 0;
	virtual void bfmeSpare006FP(void) = 0;
	virtual void bfmeSpare007FP(void) = 0;
	virtual void bfmeSpare008FP(void) = 0;
	virtual void bfmeSpare009FP(void) = 0;
	virtual void bfmeSpare010FP(void) = 0;
	virtual void bfmeSpare011FP(void) = 0;
	virtual void bfmeShowFP(int down, int line, const char *text) = 0;

	void bfmeWriteFP(const char *text);

private:
	unsigned char m_bfmeHead[4];		// 0x04
	int m_bfmeAcross;			// 0x08
	int m_bfmeLine;				// 0x0c
	unsigned char m_bfmeGap[8];		// 0x10
	int m_bfmeTop;				// 0x18
};

void BfmeThingFP::bfmeWriteFP(const char *text)
{
	bfmeShowFP(m_bfmeTop + m_bfmeAcross, m_bfmeLine, text);

	const char *at = text;
	char letter = *at;
	int width = 0;

	while (letter != 0)
	{
		++at;

		if (letter != '\n')
			++width;
		else
		{
			width = 0;

			++m_bfmeLine;

			m_bfmeAcross = 0;
		}

		letter = *at;
	}

	m_bfmeAcross += width;
}

