// Six short errands made through a table or a kept address: an item woken and
// noted, three numbers passed on, a count let go of, a marked address cleaned
// before use, and two pairs of steps taken in turn.

class BfmeItemFU
{
public:
	virtual void bfmeDoFU(void) = 0;
};

class BfmeThingFU
{
public:
	void bfmeKeepFU(BfmeItemFU *item);

private:
	unsigned char m_bfmeHead[0x20];		// 0x00
	BfmeItemFU *m_bfmeItem;			// 0x20
};

void BfmeThingFU::bfmeKeepFU(BfmeItemFU *item)
{
	item->bfmeDoFU();

	m_bfmeItem = item;
}

class BfmeThingFV
{
public:
	void bfmeGoFV(int first, int second, int third);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	void (__cdecl *m_bfmeCall)(int, int, int);	// 0x8
};

void BfmeThingFV::bfmeGoFV(int first, int second, int third)
{
	m_bfmeCall(first, second, third);
}

class BfmeCountedFW
{
public:
	virtual void bfmeDoFW(int how) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingFW
{
public:
	void bfmeReleaseFW(void);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeCountedFW *m_bfmeHeld;		// 0x4
};

void BfmeThingFW::bfmeReleaseFW(void)
{
	BfmeCountedFW *held = m_bfmeHeld;

	if (held == 0)
		return;

	int left = --held->m_bfmeCount;

	if (left > 0)
		return;

	held->bfmeDoFW(1);
}

class BfmeTargetFX
{
public:
	virtual void bfmeSpare000FX(void) = 0;
	virtual void bfmeDoFX(void) = 0;
};

class BfmeThingFX
{
public:
	void bfmeDropFX(void);

private:
	unsigned char m_bfmeHead[0xc];		// 0x0
	unsigned int m_bfmeMarked;		// 0xc
};

void BfmeThingFX::bfmeDropFX(void)
{
	unsigned int marked = m_bfmeMarked;

	if (marked != 0)
	{
		marked &= 0xFFFFFFFE;

		((BfmeTargetFX *)marked)->bfmeDoFX();

		m_bfmeMarked = 0;
	}
}


class BfmeThingGB
{
public:
	void bfmeDropGB(void);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	unsigned int m_bfmeMarked;		// 0x8
};

void BfmeThingGB::bfmeDropGB(void)
{
	unsigned int marked = m_bfmeMarked;

	if (marked != 0)
	{
		marked &= 0xFFFFFFFE;

		((BfmeTargetFX *)marked)->bfmeDoFX();

		m_bfmeMarked = 0;
	}
}

class BfmeOtherFY;

class BfmeThingFY
{
public:
	virtual void bfmeSpare000FY(void) = 0;
	virtual void bfmeSpare001FY(void) = 0;
	virtual void bfmeSpare002FY(void) = 0;
	virtual void bfmeSpare003FY(void) = 0;
	virtual void bfmeSpare004FY(void) = 0;
	virtual void bfmeSpare005FY(void) = 0;
	virtual void bfmeSpare006FY(void) = 0;
	virtual void bfmeSpare007FY(void) = 0;
	virtual void bfmeSpare008FY(void) = 0;
	virtual void bfmeSpare009FY(void) = 0;
	virtual void bfmeSpare010FY(void) = 0;
	virtual void bfmeSpare011FY(void) = 0;
	virtual void bfmeSpare012FY(void) = 0;
	virtual void bfmeSpare013FY(void) = 0;
	virtual void bfmeSpare014FY(void) = 0;
	virtual void bfmeSpare015FY(void) = 0;
	virtual void bfmeSpare016FY(void) = 0;
	virtual void bfmeSpare017FY(void) = 0;
	virtual void bfmeSpare018FY(void) = 0;
	virtual void bfmeSpare019FY(void) = 0;
	virtual void bfmeSpare020FY(void) = 0;
	virtual void bfmeSpare021FY(void) = 0;
	virtual void bfmeSpare022FY(void) = 0;
	virtual void bfmeSpare023FY(void) = 0;
	virtual void bfmeSpare024FY(void) = 0;
	virtual void bfmeSpare025FY(void) = 0;
	virtual BfmeOtherFY *bfmeMakeFY(int *where) = 0;
};

class BfmeOtherFY
{
public:
	virtual void bfmeSpare000FZ(void) = 0;
	virtual void bfmeSpare001FZ(void) = 0;
	virtual void bfmeSpare002FZ(void) = 0;
	virtual void bfmeSpare003FZ(void) = 0;
	virtual void bfmeSpare004FZ(void) = 0;
	virtual void bfmeSpare005FZ(void) = 0;
	virtual void bfmeSpare006FZ(void) = 0;
	virtual void bfmeSpare007FZ(void) = 0;
	virtual void bfmeSpare008FZ(void) = 0;
	virtual void bfmeSpare009FZ(void) = 0;
	virtual void bfmeSpare010FZ(void) = 0;
	virtual void bfmeSpare011FZ(void) = 0;
	virtual void bfmeSpare012FZ(void) = 0;
	virtual void bfmeSpare013FZ(void) = 0;
	virtual void bfmeSpare014FZ(void) = 0;
	virtual void bfmeSpare015FZ(void) = 0;
	virtual void bfmeSpare016FZ(void) = 0;
	virtual void bfmeSpare017FZ(void) = 0;
	virtual void bfmeSpare018FZ(void) = 0;
	virtual void bfmeSpare019FZ(void) = 0;
	virtual void bfmeSpare020FZ(void) = 0;
	virtual void bfmeSpare021FZ(void) = 0;
	virtual void bfmeSpare022FZ(void) = 0;
	virtual void bfmeSpare023FZ(void) = 0;
	virtual void bfmeDoFY(int *where) = 0;
	virtual void bfmeSpare025FZ(void) = 0;
	virtual void bfmeSpare026FZ(void) = 0;
	virtual void bfmeAlsoFY(int *where) = 0;
};

void bfmeGoFY(BfmeThingFY *thing, int *where)
{
	BfmeOtherFY *other = thing->bfmeMakeFY(where);

	other->bfmeDoFY(where + 1);
}

void bfmeGoGA(BfmeThingFY *thing, int *where)
{
	BfmeOtherFY *other = thing->bfmeMakeFY(where);

	other->bfmeAlsoFY(where + 1);
}

