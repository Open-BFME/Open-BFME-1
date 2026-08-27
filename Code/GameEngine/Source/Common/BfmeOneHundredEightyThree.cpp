// Four short errands that call through a table or a kept address and then get
// on with a little work of their own.

class BfmeThingCN
{
public:
	void bfmeGoCN(int first, int second, int third);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	void (__cdecl *m_bfmeCall)(int, int, int);	// 0x8
};

void BfmeThingCN::bfmeGoCN(int first, int second, int third)
{
	m_bfmeCall(first, second, third);
}

struct BfmeGotCO
{
	unsigned char m_bfmeHead[8];		// 0x0
	int m_bfmeValue;			// 0x8
};


class BfmeTargetCO
{
public:
	virtual void bfmeSpare000CO(void) = 0;
	virtual void bfmeSpare001CO(void) = 0;
	virtual void bfmeSpare002CO(void) = 0;
	virtual void bfmeSpare003CO(void) = 0;
	virtual void bfmeSpare004CO(void) = 0;
	virtual void bfmeSpare005CO(void) = 0;
	virtual void bfmeSpare006CO(void) = 0;
	virtual void bfmeSpare007CO(void) = 0;
	virtual void bfmeSpare008CO(void) = 0;
	virtual void bfmeSpare009CO(void) = 0;
	virtual void bfmeSpare010CO(void) = 0;
	virtual void bfmeSpare011CO(void) = 0;
	virtual void bfmeSpare012CO(void) = 0;
	virtual void bfmeSpare013CO(void) = 0;
	virtual void bfmeSpare014CO(void) = 0;
	virtual BfmeGotCO *bfmeGetCO(void) = 0;
};

class BfmeThingCO
{
public:
	int bfmeAskCO(void);

private:
	unsigned char m_bfmeHead[0x200];	// 0x000
	BfmeTargetCO *m_bfmeTarget;		// 0x200
};

int BfmeThingCO::bfmeAskCO(void)
{
	BfmeTargetCO *target = m_bfmeTarget;

	if (target != 0)
	{
		BfmeGotCO *got = target->bfmeGetCO();

		if (got != 0)
			return got->m_bfmeValue;
	}

	return 0;
}

class BfmeTargetCP
{
public:
	virtual void bfmeDoCP(int how) = 0;
};

class BfmeThingCP
{
public:
	void bfmeDropCP(int spare);

private:
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeTargetCP *m_bfmeTarget;		// 0x24
};

void BfmeThingCP::bfmeDropCP(int spare)
{
	BfmeTargetCP *target = m_bfmeTarget;

	if (target != 0)
	{
		target->bfmeDoCP(1);

		m_bfmeTarget = 0;
	}
}

class BfmeItemCQ
{
public:
	virtual void bfmeDoCQ(void) = 0;
};

class BfmeThingCQ
{
public:
	void bfmeKeepCQ(BfmeItemCQ *item);

private:
	unsigned char m_bfmeHead[0x7c];		// 0x00
	BfmeItemCQ *m_bfmeItem;			// 0x7c
};

void BfmeThingCQ::bfmeKeepCQ(BfmeItemCQ *item)
{
	item->bfmeDoCQ();

	m_bfmeItem = item;
}

