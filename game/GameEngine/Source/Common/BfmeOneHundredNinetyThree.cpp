// Six errands: a list asked until one answers, two pairs of counts let go of,
// a chain asked all the way along, a maker set going, and one slot of many
// cleared through a holder.

class BfmeSubET
{
public:
	virtual void bfmeSpare000ET(void);
	virtual void bfmeSpare001ET(void);
	virtual void bfmeSpare002ET(void);
	virtual void bfmeSpare003ET(void);
	virtual void bfmeSpare004ET(void);
	virtual void bfmeSpare005ET(void);
	virtual void bfmeSpare006ET(void);
	virtual void bfmeSpare007ET(void);
	virtual void bfmeSpare008ET(void);
	virtual void bfmeSpare009ET(void);
	virtual void bfmeSpare010ET(void);
	virtual void bfmeSpare011ET(void);
	virtual void bfmeSpare012ET(void);
	virtual int bfmeAskET(void);
};

struct BfmeItemET
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubET m_bfmeSub;			// 0xc
};

struct BfmeThingET
{
	unsigned char m_bfmeHead[0x1f0];	// 0x000
	BfmeItemET **m_bfmeList;		// 0x1f0
};

int bfmeFindET(BfmeThingET *thing)
{
	if (thing == 0)
		return 0;

	BfmeItemET **at = thing->m_bfmeList;

	while (*at != 0)
	{
		int answer = (*at)->m_bfmeSub.bfmeAskET();

		if (answer != 0)
			return answer;

		++at;
	}

	return 0;
}

class BfmeCountedEU
{
public:
	virtual void bfmeGoneEU(void) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingEU
{
public:
	void bfmeClearEU(void);
	void bfmeAlsoEU(void);

private:
	BfmeCountedEU *m_bfmeFirst;		// 0x0
	BfmeCountedEU *m_bfmeSecond;		// 0x4
};

void BfmeThingEU::bfmeClearEU(void)
{
	BfmeCountedEU *second = m_bfmeSecond;

	if (second != 0)
	{
		if (--second->m_bfmeCount == 0)
			second->bfmeGoneEU();

		m_bfmeSecond = 0;
	}

	BfmeCountedEU *first = m_bfmeFirst;

	if (first != 0)
	{
		if (--first->m_bfmeCount == 0)
			first->bfmeGoneEU();

		m_bfmeFirst = 0;
	}
}

void BfmeThingEU::bfmeAlsoEU(void)
{
	BfmeCountedEU *second = m_bfmeSecond;

	if (second != 0)
	{
		if (--second->m_bfmeCount == 0)
			second->bfmeGoneEU();

		m_bfmeSecond = 0;
	}

	BfmeCountedEU *first = m_bfmeFirst;

	if (first != 0)
	{
		if (--first->m_bfmeCount == 0)
			first->bfmeGoneEU();

		m_bfmeFirst = 0;
	}
}

class BfmeThingEQ
{
public:
	virtual void bfmeSpare000EQ(void) = 0;
	virtual unsigned char bfmeDoEQ(void *what) = 0;

	unsigned char bfmeAskEQ(void *what);

	BfmeThingEQ *m_bfmeNext;		// 0x4
};

unsigned char BfmeThingEQ::bfmeAskEQ(void *what)
{
	BfmeThingEQ *at = this;

	while (at != 0)
	{
		if (at->bfmeDoEQ(what) == 0)
			return 0;

		at = at->m_bfmeNext;
	}

	return 1;
}


class BfmeMadeER;

class BfmeTargetER
{
public:
	virtual void bfmeSpare000ER(void) = 0;
	virtual void bfmeSpare001ER(void) = 0;
	virtual BfmeMadeER *bfmeMakeER(void) = 0;
};

class BfmeMadeER
{
public:
	unsigned char m_bfmeHead[0x4c];		// 0x00
	void *m_bfmeBack;			// 0x4c
};


class BfmeThingER
{
public:
	virtual void bfmeSpare000EV(void) = 0;
	virtual void bfmeSpare001EV(void) = 0;
	virtual void bfmeSpare002EV(void) = 0;
	virtual void bfmeSpare003EV(void) = 0;
	virtual void bfmeSpare004EV(void) = 0;
	virtual void bfmeSpare005EV(void) = 0;
	virtual void bfmeSpare006EV(void) = 0;
	virtual void bfmeSpare007EV(void) = 0;
	virtual void bfmeSpare008EV(void) = 0;
	virtual void bfmeSpare009EV(void) = 0;
	virtual unsigned char bfmeAskER(void) = 0;
	virtual void bfmeFixER(void) = 0;

	BfmeMadeER *bfmeGoER(void);

private:
	unsigned char m_bfmeHead[0x64];		// 0x04
	void *m_bfmeOther;			// 0x68
	unsigned char m_bfmeGap[4];		// 0x6c
	BfmeTargetER *m_bfmeTarget;		// 0x70
};

BfmeMadeER *BfmeThingER::bfmeGoER(void)
{
	if (bfmeAskER() == 0)
		bfmeFixER();

	if (m_bfmeTarget == 0)
		return 0;

	BfmeMadeER *made = m_bfmeTarget->bfmeMakeER();

	if (made != 0)
		made->m_bfmeBack = m_bfmeOther;

	return made;
}

class BfmeTargetES
{
public:
	virtual void bfmeDoES(int how) = 0;
};

struct BfmeSlotsES
{
	unsigned char m_bfmeHead[4];		// 0x00
	BfmeTargetES *m_bfmeItems[14];		// 0x04
	int m_bfmeMarks[14];			// 0x3c
};

class BfmeThingES
{
public:
	void bfmeDropES(int which);

private:
	unsigned char m_bfmeHead[0x2e0];	// 0x000
	BfmeSlotsES *m_bfmeSlots;		// 0x2e0
};

void BfmeThingES::bfmeDropES(int which)
{
	BfmeSlotsES *slots = m_bfmeSlots;

	if (slots == 0)
		return;

	BfmeTargetES *target = slots->m_bfmeItems[which];

	if (target != 0)
	{
		target->bfmeDoES(1);

		slots->m_bfmeItems[which] = 0;
		slots->m_bfmeMarks[which] = 0;
	}
}

