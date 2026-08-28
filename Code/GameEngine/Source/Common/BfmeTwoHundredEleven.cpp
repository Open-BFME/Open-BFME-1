// Four errands: a helper stopped and let go of, a first piece and then a whole
// row each told to finish, a piece asked and made to settle before its next is
// read, and a helper opened, pointed and closed around a note taken down.

class BfmeItemIF
{
public:
	virtual void bfmeGoneIF(int how) = 0;
	virtual void bfmeSpare001IF(void) = 0;
	virtual void bfmeSpare002IF(void) = 0;
	virtual void bfmeSpare003IF(void) = 0;
	virtual void bfmeSpare004IF(void) = 0;
	virtual void bfmeStopIF(void *what) = 0;
};

class BfmeThingIF
{
public:
	void bfmeDropIF(void *what);

private:
	unsigned char m_bfmeHead[0x2c];		// 0x00
	BfmeItemIF *m_bfmeItem;			// 0x2c
};

void BfmeThingIF::bfmeDropIF(void *what)
{
	BfmeItemIF *item = m_bfmeItem;

	if (item != 0)
	{
		item->bfmeStopIF(what);

		if (m_bfmeItem != 0)
			m_bfmeItem->bfmeGoneIF(1);

		m_bfmeItem = 0;
	}
}

class BfmeItemIG
{
public:
	virtual void bfmeSpare000IG(void) = 0;
	virtual void bfmeDoIG(void) = 0;
};

class BfmeThingIG
{
public:
	void bfmeClearIG(void);

private:
	BfmeItemIG *m_bfmeOne;			// 0x0
	BfmeItemIG **m_bfmeBegin;		// 0x4
	BfmeItemIG **m_bfmeEnd;			// 0x8
};

void BfmeThingIG::bfmeClearIG(void)
{
	BfmeItemIG *one = m_bfmeOne;

	if (one != 0)
		one->bfmeDoIG();

	for (BfmeItemIG **at = m_bfmeBegin; at != m_bfmeEnd; ++at)
		(*at)->bfmeDoIG();
}


class BfmeItemIH
{
public:
	virtual void bfmeSpare000IH(void) = 0;
	virtual void bfmeSpare001IH(void) = 0;
	virtual void bfmeSpare002IH(void) = 0;
	virtual void bfmeSpare003IH(void) = 0;
	virtual void bfmeSpare004IH(void) = 0;
	virtual void bfmeSpare005IH(void) = 0;
	virtual void bfmeSpare006IH(void) = 0;
	virtual void bfmeSpare007IH(void) = 0;
	virtual void bfmeSpare008IH(void) = 0;
	virtual void bfmeSpare009IH(void) = 0;
	virtual unsigned char bfmeAskIH(void) = 0;
	virtual void bfmeDoIH(void) = 0;

	unsigned char m_bfmeGap[0x10];		// 0x04
	BfmeItemIH *m_bfmeNext;			// 0x14
	unsigned char m_bfmeMore[0x14];		// 0x18
	int m_bfmeValue;			// 0x2c
};

class BfmeThingIH
{
public:
	int bfmeGetIH(void);

private:
	BfmeItemIH *m_bfmeItem;			// 0x0
};

int BfmeThingIH::bfmeGetIH(void)
{
	BfmeItemIH *at = m_bfmeItem;

	if (at != 0)
	{
		if (at->bfmeAskIH() == 0)
			at->bfmeDoIH();

		at = at->m_bfmeNext;

		if (at != 0)
			return at->m_bfmeValue;
	}

	return 1;
}

class BfmeHelpII
{
public:
	virtual void bfmeSpare000II(void) = 0;
	virtual void bfmeSpare001II(void) = 0;
	virtual void bfmeSpare002II(void) = 0;
	virtual void bfmeSpare003II(void) = 0;
	virtual void bfmeSpare004II(void) = 0;
	virtual void bfmeStartII(void) = 0;
	virtual void bfmeSpare006II(void) = 0;
	virtual void bfmeSpare007II(void) = 0;
	virtual void bfmeEndII(int how) = 0;
	virtual void bfmeSpare009II(void) = 0;
	virtual void bfmeSpare010II(void) = 0;
	virtual void bfmeSpare011II(void) = 0;
	virtual void bfmeSpare012II(void) = 0;
	virtual void bfmeSpare013II(void) = 0;
	virtual void bfmePointII(void *what) = 0;
};

class BfmeThingII
{
public:
	void bfmeGoII(void *what, int note);

private:
	unsigned char m_bfmeHead[0x30];		// 0x00
	BfmeHelpII *m_bfmeHelp;			// 0x30
	unsigned char m_bfmeGap[0x14];		// 0x34
	int m_bfmeNote;				// 0x48
};

void BfmeThingII::bfmeGoII(void *what, int note)
{
	m_bfmeHelp->bfmeStartII();

	m_bfmeHelp->bfmePointII(what);

	m_bfmeNote = note;

	m_bfmeHelp->bfmeEndII(0x34);
}

