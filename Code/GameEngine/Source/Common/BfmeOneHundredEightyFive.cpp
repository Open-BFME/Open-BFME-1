// Five errands made through a table: a question forwarded, two counts let go
// of, a thing dropped, and a pair of steps taken in turn.

class BfmeTargetCW
{
public:
	virtual void bfmeSpare000CW(void) = 0;
	virtual unsigned char bfmeDoCW(void *first, void *second) = 0;
};

unsigned char bfmeAskCW(void *first, void *second, BfmeTargetCW *target)
{
	if (target == 0)
		return 0;

	return target->bfmeDoCW(first, second);
}

class BfmeTargetCX
{
public:
	virtual void bfmeDoCX(int how) = 0;
};

class BfmeThingCX
{
public:
	void bfmeDropCX(int spare);

private:
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeTargetCX *m_bfmeTarget;		// 0x24
};

void BfmeThingCX::bfmeDropCX(int spare)
{
	BfmeTargetCX *target = m_bfmeTarget;

	if (target != 0)
		target->bfmeDoCX(1);

	m_bfmeTarget = 0;
}

class BfmeCountedCY
{
public:
	virtual void bfmeDoCY(int how) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingCY
{
public:
	void bfmeReleaseCY(void);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeCountedCY *m_bfmeHeld;		// 0x4
};

void BfmeThingCY::bfmeReleaseCY(void)
{
	BfmeCountedCY *held = m_bfmeHeld;

	if (held == 0)
		return;

	int left = --held->m_bfmeCount;

	if (left > 0)
		return;

	held->bfmeDoCY(1);
}

class BfmeCountedCZ
{
public:
	virtual void bfmeDoCZ(int how);

	int m_bfmeCount;			// 0x4
};

struct BfmeOwnerCZ
{
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeCountedCZ m_bfmeSub;		// 0x24
};

class BfmeThingCZ
{
public:
	void bfmeReleaseCZ(void);

private:
	BfmeOwnerCZ *m_bfmeOwner;		// 0x0
};

void BfmeThingCZ::bfmeReleaseCZ(void)
{
	BfmeOwnerCZ *owner = m_bfmeOwner;

	if (owner == 0)
		return;

	BfmeCountedCZ *counted = &owner->m_bfmeSub;
	int left = --counted->m_bfmeCount;

	if (left > 0)
		return;

	counted->bfmeDoCZ(1);
}


class BfmeOtherDA;

class BfmeThingDA
{
public:
	virtual void bfmeSpare000DA(void) = 0;
	virtual void bfmeSpare001DA(void) = 0;
	virtual void bfmeSpare002DA(void) = 0;
	virtual void bfmeSpare003DA(void) = 0;
	virtual void bfmeSpare004DA(void) = 0;
	virtual void bfmeSpare005DA(void) = 0;
	virtual void bfmeSpare006DA(void) = 0;
	virtual void bfmeSpare007DA(void) = 0;
	virtual void bfmeSpare008DA(void) = 0;
	virtual void bfmeSpare009DA(void) = 0;
	virtual void bfmeSpare010DA(void) = 0;
	virtual void bfmeSpare011DA(void) = 0;
	virtual void bfmeSpare012DA(void) = 0;
	virtual void bfmeSpare013DA(void) = 0;
	virtual void bfmeSpare014DA(void) = 0;
	virtual void bfmeSpare015DA(void) = 0;
	virtual void bfmeSpare016DA(void) = 0;
	virtual void bfmeSpare017DA(void) = 0;
	virtual void bfmeSpare018DA(void) = 0;
	virtual void bfmeSpare019DA(void) = 0;
	virtual void bfmeSpare020DA(void) = 0;
	virtual void bfmeSpare021DA(void) = 0;
	virtual void bfmeSpare022DA(void) = 0;
	virtual void bfmeSpare023DA(void) = 0;
	virtual void bfmeSpare024DA(void) = 0;
	virtual void bfmeSpare025DA(void) = 0;
	virtual BfmeOtherDA *bfmeMakeDA(int *where) = 0;
};

class BfmeOtherDA
{
public:
	virtual void bfmeSpare000DB(void) = 0;
	virtual void bfmeSpare001DB(void) = 0;
	virtual void bfmeSpare002DB(void) = 0;
	virtual void bfmeSpare003DB(void) = 0;
	virtual void bfmeSpare004DB(void) = 0;
	virtual void bfmeSpare005DB(void) = 0;
	virtual void bfmeSpare006DB(void) = 0;
	virtual void bfmeSpare007DB(void) = 0;
	virtual void bfmeSpare008DB(void) = 0;
	virtual void bfmeSpare009DB(void) = 0;
	virtual void bfmeSpare010DB(void) = 0;
	virtual void bfmeSpare011DB(void) = 0;
	virtual void bfmeSpare012DB(void) = 0;
	virtual void bfmeSpare013DB(void) = 0;
	virtual void bfmeSpare014DB(void) = 0;
	virtual void bfmeSpare015DB(void) = 0;
	virtual void bfmeSpare016DB(void) = 0;
	virtual void bfmeSpare017DB(void) = 0;
	virtual void bfmeSpare018DB(void) = 0;
	virtual void bfmeSpare019DB(void) = 0;
	virtual void bfmeSpare020DB(void) = 0;
	virtual void bfmeSpare021DB(void) = 0;
	virtual void bfmeSpare022DB(void) = 0;
	virtual void bfmeSpare023DB(void) = 0;
	virtual void bfmeSpare024DB(void) = 0;
	virtual void bfmeSpare025DB(void) = 0;
	virtual void bfmeSpare026DB(void) = 0;
	virtual void bfmeSpare027DB(void) = 0;
	virtual void bfmeSpare028DB(void) = 0;
	virtual void bfmeDoDA(int *where) = 0;
};

void bfmeGoDA(BfmeThingDA *thing, int *where)
{
	BfmeOtherDA *other = thing->bfmeMakeDA(where);

	other->bfmeDoDA(where + 1);
}
