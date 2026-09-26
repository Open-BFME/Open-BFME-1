// Four more: two gated accumulators, a planar difference returned by value,
// and a bounded attach.

class BfmeClockCJ
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeNow;						// +0x3C
	char m_bfmeGap[0x50];					// +0x40
	unsigned char m_bfmeEnabled;				// +0x90
};

extern BfmeClockCJ *g_bfmeSwitchCJ;				// retail 0x012F0898

class Gen_000E8870
{
public:
	void bfmeAddA(int amount);
	void bfmeAddB(int amount);

private:
	int m_bfmeHead[71];					// +0x000
	int m_bfmeFirst;					// +0x11C
	int m_bfmeSecond;					// +0x120
};

// ?bfmeAddA@Gen_000E8870@@QAEXH@Z
void Gen_000E8870::bfmeAddA(int amount)
{
	unsigned char enabled = g_bfmeSwitchCJ->m_bfmeEnabled;

	if (enabled)
		m_bfmeFirst = m_bfmeFirst + amount;
}

// ?bfmeAddB@Gen_000E8870@@QAEXH@Z
void Gen_000E8870::bfmeAddB(int amount)
{
	unsigned char enabled = g_bfmeSwitchCJ->m_bfmeEnabled;

	if (enabled)
		m_bfmeSecond = m_bfmeSecond + amount;
}

class BfmeVec2DG
{
public:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
};

class BfmeVec3DG
{
public:
	BfmeVec3DG(void)
	{
	}

	BfmeVec3DG(const BfmeVec3DG &other)
	{
		m_bfmeX = other.m_bfmeX;
		m_bfmeY = other.m_bfmeY;
		m_bfmeZ = other.m_bfmeZ;
	}

	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
};

class Gen_00148960
{
public:
	BfmeVec3DG bfmeDelta(const BfmeVec2DG *point) const;

private:
	int m_bfmeHead[14];					// +0x00
	float m_bfmeX;						// +0x38
	float m_bfmeY;						// +0x3C
};

// ?bfmeDelta@Gen_00148960@@QBE?AVBfmeVec3DG@@PBVBfmeVec2DG@@@Z
BfmeVec3DG Gen_00148960::bfmeDelta(const BfmeVec2DG *point) const
{
	BfmeVec3DG delta;

	delta.m_bfmeX = point->m_bfmeX - m_bfmeX;
	delta.m_bfmeY = point->m_bfmeY - m_bfmeY;
	delta.m_bfmeZ = 0.0f;

	return delta;
}

class BfmeChildDG
{
public:
	int m_bfmeHead[16];					// +0x00
	void *m_bfmeParent;					// +0x40
};

class Gen_001A5D90
{
public:
	void bfmeAdd(BfmeChildDG *child);

private:
	int m_bfmeHead[8];					// +0x00
	BfmeChildDG *m_bfmeSlots[11];				// +0x20
	int m_bfmeCount;					// +0x4C
};

// ?bfmeAdd@Gen_001A5D90@@QAEXPAVBfmeChildDG@@@Z
void Gen_001A5D90::bfmeAdd(BfmeChildDG *child)
{
	int count = m_bfmeCount;

	if (count < 8)
	{
		m_bfmeSlots[count] = child;

		++m_bfmeCount;
	}

	child->m_bfmeParent = this;
}
