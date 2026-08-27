// Three errands: a run told two things, a held thing swapped for another with
// the counts kept straight, and two things compared for sameness.

class BfmeItemGY
{
public:
	virtual void bfmeSpare000GY(void) = 0;
	virtual void bfmeSpare001GY(void) = 0;
	virtual void bfmeSpare002GY(void) = 0;
	virtual void bfmeDoGY(void *first, void *second) = 0;
};

class BfmeThingGY
{
public:
	void bfmeTellGY(void *first, void *second);

private:
	BfmeItemGY **m_bfmeBegin;		// 0x0
	BfmeItemGY **m_bfmeEnd;			// 0x4
};

void BfmeThingGY::bfmeTellGY(void *first, void *second)
{
	BfmeItemGY **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoGY(first, second);

		++at;
	}
}

class BfmeCountedGW
{
public:
	virtual void bfmeDoGW(int how) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingGW
{
public:
	void bfmeSetGW(BfmeCountedGW *item);

private:
	BfmeCountedGW *m_bfmeHeld;		// 0x0
};

void BfmeThingGW::bfmeSetGW(BfmeCountedGW *item)
{
	BfmeCountedGW *held = m_bfmeHeld;

	if (item == held)
		return;

	if (held != 0)
	{
		int left = --held->m_bfmeCount;

		if (left <= 0)
			held->bfmeDoGW(1);

		m_bfmeHeld = 0;
	}

	m_bfmeHeld = item;

	if (item != 0)
		++item->m_bfmeCount;
}


class BfmeThingGX;

class BfmeThingGX
{
public:
	virtual void bfmeSpare000GX(void) = 0;
	virtual void bfmeSpare001GX(void) = 0;
	virtual void bfmeSpare002GX(void) = 0;
	virtual void bfmeSpare003GX(void) = 0;
	virtual unsigned char bfmeMatchGX(BfmeThingGX *other) = 0;
	virtual int bfmeKindGX(void) = 0;
};

int bfmeSameGX(BfmeThingGX *left, BfmeThingGX *right)
{
	if (left->bfmeKindGX() == right->bfmeKindGX())
	{
		if (left->bfmeMatchGX(right) != 0)
			return 1;
	}

	return 0;
}

