// Three errands: a piece asked and settled before its next is read, three rows
// of pieces each run to the end, and a target marked and asked before it is
// handed the piece.

class BfmeItemIJ
{
public:
	virtual void bfmeSpare000IJ(void) = 0;
	virtual void bfmeSpare001IJ(void) = 0;
	virtual void bfmeSpare002IJ(void) = 0;
	virtual void bfmeSpare003IJ(void) = 0;
	virtual void bfmeSpare004IJ(void) = 0;
	virtual void bfmeSpare005IJ(void) = 0;
	virtual void bfmeSpare006IJ(void) = 0;
	virtual void bfmeSpare007IJ(void) = 0;
	virtual void bfmeSpare008IJ(void) = 0;
	virtual void bfmeSpare009IJ(void) = 0;
	virtual unsigned char bfmeAskIJ(void) = 0;
	virtual void bfmeDoIJ(void) = 0;

	unsigned char m_bfmeGap[0x10];		// 0x04
	BfmeItemIJ *m_bfmeNext;			// 0x14
	unsigned char m_bfmeMore[0x18];		// 0x18
	int m_bfmeValue;			// 0x30
};

class BfmeThingIJ
{
public:
	int bfmeGetIJ(void);

private:
	BfmeItemIJ *m_bfmeItem;			// 0x0
};

int BfmeThingIJ::bfmeGetIJ(void)
{
	BfmeItemIJ *at = m_bfmeItem;

	if (at != 0)
	{
		if (at->bfmeAskIJ() == 0)
			at->bfmeDoIJ();

		at = at->m_bfmeNext;

		if (at != 0)
			return at->m_bfmeValue;
	}

	return 1;
}


class BfmeItemIK
{
public:
	virtual void bfmeSpare000IK(void) = 0;
	virtual void bfmeSpare001IK(void) = 0;
	virtual void bfmeSpare002IK(void) = 0;
	virtual void bfmeSpare003IK(void) = 0;
	virtual void bfmeSpare004IK(void) = 0;
	virtual void bfmeSpare005IK(void) = 0;
	virtual void bfmeSpare006IK(void) = 0;
	virtual void bfmeSpare007IK(void) = 0;
	virtual void bfmeDoIK(void) = 0;
};

class BfmeThingIK
{
public:
	void bfmeClearIK(void);

private:
	unsigned char m_bfmeHead[0x150];	// 0x000
	BfmeItemIK **m_bfmeRows[3];		// 0x150
};

void BfmeThingIK::bfmeClearIK(void)
{
	BfmeItemIK ***row = m_bfmeRows;

	for (int left = 3; left != 0; --left)
	{
		BfmeItemIK **at = *row;

		while (at != 0 && *at != 0)
		{
			(*at)->bfmeDoIK();

			++at;
		}

		++row;
	}
}

struct BfmePairIN
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};

class BfmeItemIN
{
public:
	virtual void bfmeSpare000IN(void) = 0;
};


class BfmeTargetIN
{
public:
	virtual void bfmeSpare000IN(void) = 0;
	virtual void bfmeSpare001IN(void) = 0;
	virtual void bfmeSpare002IN(void) = 0;
	virtual unsigned char bfmeAskIN(void) = 0;
	virtual void bfmeSpare004IN(void) = 0;
	virtual void bfmeSpare005IN(void) = 0;
	virtual void bfmeSpare006IN(void) = 0;
	virtual void bfmeSpare007IN(void) = 0;
	virtual void bfmeSpare008IN(void) = 0;
	virtual void bfmeSpare009IN(void) = 0;
	virtual void bfmeMarkIN(BfmePairIN *both) = 0;
	virtual void bfmeSpare011IN(void) = 0;
	virtual void bfmeTakeIN(BfmeItemIN *item) = 0;
};

class BfmeThingIN
{
public:
	void bfmeGoIN(BfmeTargetIN *target);

private:
	unsigned char m_bfmeHead[0x40];		// 0x00
	BfmeItemIN *m_bfmeItem;			// 0x40
};

void BfmeThingIN::bfmeGoIN(BfmeTargetIN *target)
{
	BfmePairIN both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	target->bfmeMarkIN(&both);

	if (target->bfmeAskIN() != 0)
	{
		BfmeItemIN *item = m_bfmeItem;

		if (item != 0)
			target->bfmeTakeIN(item);
	}
}

