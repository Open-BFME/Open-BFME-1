// Three errands: two charges let go of when the last hold ends, a pair of marks
// set on a newcomer before two lists take it in, and a target marked and then
// asked before it is handed the piece.

class BfmeItemHO
{
public:
	virtual void bfmeGoneHO(void) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingHO
{
public:
	void bfmeClearHO(void);

private:
	unsigned char m_bfmeHead[0x2fd8];	// 0x0000
	BfmeItemHO *m_bfmeFirst;		// 0x2fd8
	BfmeItemHO *m_bfmeSecond;		// 0x2fdc
};

void BfmeThingHO::bfmeClearHO(void)
{
	BfmeItemHO *first = m_bfmeFirst;

	if (first != 0)
	{
		if (--first->m_bfmeCount == 0)
			first->bfmeGoneHO();

		m_bfmeFirst = 0;
	}

	BfmeItemHO *second = m_bfmeSecond;

	if (second != 0)
	{
		if (--second->m_bfmeCount == 0)
			second->bfmeGoneHO();

		m_bfmeSecond = 0;
	}
}

struct BfmePairHP
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};


class BfmeItemHP
{
public:
	virtual void bfmeSpare000HP(void) = 0;
	virtual void bfmeSpare001HP(void) = 0;
	virtual void bfmeSpare002HP(void) = 0;
	virtual void bfmeSpare003HP(void) = 0;
	virtual unsigned char bfmeIsHP(void) = 0;
	virtual void bfmeSpare005HP(void) = 0;
	virtual void bfmeSpare006HP(void) = 0;
	virtual void bfmeSpare007HP(void) = 0;
	virtual void bfmeSpare008HP(void) = 0;
	virtual void bfmeSpare009HP(void) = 0;
	virtual void bfmeMarkHP(BfmePairHP *both) = 0;
};

class BfmeListHP
{
public:
	virtual void bfmeAddHP(BfmeItemHP *item);

private:
	unsigned char m_bfmeBody[0x44];		// 0x04
};

class BfmeThingHP
{
public:
	void bfmeTakeHP(BfmeItemHP *item);

private:
	unsigned char m_bfmeHead[4];		// 0x00
	BfmeListHP m_bfmeFirstList;		// 0x04
	BfmeListHP m_bfmeSecondList;		// 0x4c
};

void BfmeThingHP::bfmeTakeHP(BfmeItemHP *item)
{
	if (item->bfmeIsHP() == 0)
	{
		BfmePairHP both;

		both.m_bfmeFirst = 1;
		both.m_bfmeSecond = 1;

		item->bfmeMarkHP(&both);

		m_bfmeFirstList.bfmeAddHP(item);
		m_bfmeSecondList.bfmeAddHP(item);
	}
}

struct BfmePairHQ
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};

class BfmeItemHQ
{
public:
	virtual void bfmeSpare000HQ(void) = 0;
};


class BfmeTargetHQ
{
public:
	virtual void bfmeSpare000HQ(void) = 0;
	virtual void bfmeSpare001HQ(void) = 0;
	virtual void bfmeSpare002HQ(void) = 0;
	virtual unsigned char bfmeAskHQ(void) = 0;
	virtual void bfmeSpare004HQ(void) = 0;
	virtual void bfmeSpare005HQ(void) = 0;
	virtual void bfmeSpare006HQ(void) = 0;
	virtual void bfmeSpare007HQ(void) = 0;
	virtual void bfmeSpare008HQ(void) = 0;
	virtual void bfmeSpare009HQ(void) = 0;
	virtual void bfmeMarkHQ(BfmePairHQ *both) = 0;
	virtual void bfmeSpare011HQ(void) = 0;
	virtual void bfmeTakeHQ(BfmeItemHQ *item) = 0;
};

class BfmeThingHQ
{
public:
	void bfmeGoHQ(BfmeTargetHQ *target);

private:
	unsigned char m_bfmeHead[0x40];		// 0x00
	BfmeItemHQ *m_bfmeItem;			// 0x40
};

void BfmeThingHQ::bfmeGoHQ(BfmeTargetHQ *target)
{
	BfmePairHQ both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	target->bfmeMarkHQ(&both);

	if (target->bfmeAskHQ() != 0)
	{
		BfmeItemHQ *item = m_bfmeItem;

		if (item != 0)
			target->bfmeTakeHQ(item);
	}
}

