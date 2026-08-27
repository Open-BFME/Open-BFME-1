// Five errands: one charge swapped for another, a part asking its whole first
// and then telling it, a maker set going, a count let go of, and a queue
// drained one at a time.

class BfmeItemGH
{
public:
	virtual void bfmeAddGH(void) = 0;
	virtual void bfmeDropGH(void) = 0;
};

class BfmeThingGH
{
public:
	void bfmeSetGH(BfmeItemGH *item);

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	BfmeItemGH *m_bfmeItem;			// 0x18
};

void BfmeThingGH::bfmeSetGH(BfmeItemGH *item)
{
	BfmeItemGH *old = m_bfmeItem;

	if (old != 0)
		old->bfmeDropGH();

	m_bfmeItem = item;

	if (item != 0)
		item->bfmeAddGH();
}


class BfmeHostGI
{
public:
	virtual void bfmeSpare000GI(void) = 0;
	virtual void bfmeSpare001GI(void) = 0;
	virtual void bfmeSpare002GI(void) = 0;
	virtual void bfmeDoGI(void *what) = 0;
	virtual unsigned char bfmeAskGI(void *what) = 0;
};

class BfmeSubGI
{
public:
	void bfmeGoGI(void *what, int spare, int more);

	unsigned char m_bfmeHead[4];		// 0x0
};

void BfmeSubGI::bfmeGoGI(void *what, int spare, int more)
{
	BfmeHostGI *host = (BfmeHostGI *)((char *)this - 4);

	if (host->bfmeAskGI(what) != 0)
		host->bfmeDoGI(what);
}


class BfmeOtherGJ
{
public:
	virtual void bfmeSpare000GJ(void) = 0;
	virtual void bfmeSpare001GJ(void) = 0;
	virtual void bfmeSpare002GJ(void) = 0;
	virtual void bfmeSpare003GJ(void) = 0;
	virtual void bfmeSpare004GJ(void) = 0;
	virtual void bfmeSpare005GJ(void) = 0;
	virtual void bfmeSpare006GJ(void) = 0;
	virtual void bfmeSpare007GJ(void) = 0;
	virtual void bfmeSpare008GJ(void) = 0;
	virtual void bfmeSpare009GJ(void) = 0;
	virtual void bfmeSpare010GJ(void) = 0;
	virtual void bfmeSpare011GJ(void) = 0;
	virtual void bfmeSpare012GJ(void) = 0;
	virtual void bfmeSpare013GJ(void) = 0;
	virtual void bfmeSpare014GJ(void) = 0;
	virtual void bfmeSpare015GJ(void) = 0;
	virtual void bfmeSpare016GJ(void) = 0;
	virtual void bfmeSpare017GJ(void) = 0;
	virtual void bfmeSpare018GJ(void) = 0;
	virtual void bfmeSpare019GJ(void) = 0;
	virtual void bfmeSpare020GJ(void) = 0;
	virtual void bfmeDoGJ(void) = 0;
};

class BfmeSubGJ
{
public:
	virtual void bfmeSpare000GK(void);
	virtual void bfmeSpare001GK(void);
	virtual void bfmeSpare002GK(void);
	virtual void bfmeSpare003GK(void);
	virtual void bfmeSpare004GK(void);
	virtual void bfmeSpare005GK(void);
	virtual void bfmeSpare006GK(void);
	virtual BfmeOtherGJ *bfmeMakeGJ(void);
};

struct BfmeItemGJ
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubGJ m_bfmeSub;			// 0xc
};


class BfmeThingGJ
{
public:
	virtual void bfmeSpare000GJ(void) = 0;
	virtual unsigned char bfmeAskGJ(void) = 0;

	void bfmeGoGJ(int spare);

private:
	unsigned char m_bfmeHead[0x18];		// 0x04
	BfmeItemGJ *m_bfmeItem;			// 0x1c
};

void BfmeThingGJ::bfmeGoGJ(int spare)
{
	if (bfmeAskGJ() == 0)
		return;

	BfmeOtherGJ *other = m_bfmeItem->m_bfmeSub.bfmeMakeGJ();

	other->bfmeDoGJ();
}

class BfmeCountedGL
{
public:
	virtual void bfmeDoGL(int how) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingGL
{
public:
	void bfmeReleaseGL(void);

private:
	BfmeCountedGL *m_bfmeHeld;		// 0x0
};

void BfmeThingGL::bfmeReleaseGL(void)
{
	BfmeCountedGL *held = m_bfmeHeld;

	if (held == 0)
		return;

	int left = --held->m_bfmeCount;

	if (left <= 0)
		held->bfmeDoGL(1);

	m_bfmeHeld = 0;
}


class BfmeItemGM;

class BfmeItemGM
{
public:
	virtual void bfmeSpare000GM(void) = 0;
	virtual void bfmeSpare001GM(void) = 0;
	virtual void bfmeSpare002GM(void) = 0;
	virtual void bfmeSpare003GM(void) = 0;
	virtual void bfmeSpare004GM(void) = 0;
	virtual void bfmeSpare005GM(void) = 0;
	virtual void bfmeSpare006GM(void) = 0;
	virtual void bfmeDoGM(void) = 0;
};

class BfmeThingGM
{
public:
	virtual void bfmeSpare000GN(void) = 0;
	virtual void bfmeSpare001GN(void) = 0;
	virtual void bfmeSpare002GN(void) = 0;
	virtual void bfmeSpare003GN(void) = 0;
	virtual void bfmeSpare004GN(void) = 0;
	virtual void bfmeSpare005GN(void) = 0;
	virtual void bfmeSpare006GN(void) = 0;
	virtual void bfmeSpare007GN(void) = 0;
	virtual void bfmeSpare008GN(void) = 0;
	virtual void bfmeSpare009GN(void) = 0;
	virtual void bfmeSpare010GN(void) = 0;
	virtual void bfmeSpare011GN(void) = 0;
	virtual void bfmeSpare012GN(void) = 0;
	virtual BfmeItemGM *bfmeTakeGM(void) = 0;

	void bfmeDrainGM(void);
};

void BfmeThingGM::bfmeDrainGM(void)
{
	BfmeItemGM *item = bfmeTakeGM();

	while (item != 0)
	{
		item->bfmeDoGM();

		item = bfmeTakeGM();
	}
}

