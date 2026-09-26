// Six small accessors: an emptiness test on a self-linked list, two getters
// that fall back on a shared default, and three setters that mark a global
// before storing.
//
// The emptiness test compares the node's own successor against the node, and
// the result of that comparison is what the caller gets back.

class BfmeNodeBG
{
public:
	BfmeNodeBG *m_bfmeNext;					// +0x00
};

class Gen_001506E0
{
public:
	bool bfmeIsEmpty(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeNodeBG *m_bfmeNode;					// +0x04
};

// ?bfmeIsEmpty@Gen_001506E0@@QBE_NXZ
bool Gen_001506E0::bfmeIsEmpty(void) const
{
	BfmeNodeBG *node = m_bfmeNode;

	return node->m_bfmeNext == node;
}

class BfmeThingBG
{
public:
	int m_bfmeHead[4];					// +0x00
	int m_bfmeFieldA;					// +0x10
	int m_bfmeFieldB;					// +0x14
};

extern int g_bfmeDefaultBG[2];					// retail 0x01336E50

class Gen_000EC5E0
{
public:
	int *bfmeFieldA(void) const;
	int *bfmeFieldB(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeThingBG *m_bfmeThing;				// +0x04
};

// ?bfmeFieldA@Gen_000EC5E0@@QBEPAHXZ
int *Gen_000EC5E0::bfmeFieldA(void) const
{
	BfmeThingBG *thing = m_bfmeThing;

	if (!thing)
		return g_bfmeDefaultBG;

	return &thing->m_bfmeFieldA;
}

// ?bfmeFieldB@Gen_000EC5E0@@QBEPAHXZ
int *Gen_000EC5E0::bfmeFieldB(void) const
{
	BfmeThingBG *thing = m_bfmeThing;

	if (!thing)
		return g_bfmeDefaultBG;

	return &thing->m_bfmeFieldB;
}

extern int g_bfmeDirtyBG;					// retail 0x012EF418

class Gen_0018F210
{
public:
	void bfmeSetA(bool value);
	void bfmeSetB(bool value);
	void bfmeSetC(int value);

private:
	char m_bfmeHead[0x32];					// +0x00
	bool m_bfmeA;						// +0x32
	char m_bfmeGap[0x2D];					// +0x33
	bool m_bfmeB;						// +0x60
	char m_bfmeGap2[0x13];					// +0x61
	int m_bfmeC;						// +0x74
};

// ?bfmeSetA@Gen_0018F210@@QAEX_N@Z
void Gen_0018F210::bfmeSetA(bool value)
{
	g_bfmeDirtyBG |= 1;

	m_bfmeA = value;
}

// ?bfmeSetB@Gen_0018F210@@QAEX_N@Z
void Gen_0018F210::bfmeSetB(bool value)
{
	g_bfmeDirtyBG |= 1;

	m_bfmeB = value;
}

// ?bfmeSetC@Gen_0018F210@@QAEXH@Z
void Gen_0018F210::bfmeSetC(int value)
{
	g_bfmeDirtyBG |= 1;

	m_bfmeC = value;
}

// The carved retail boundary at 0x000EC5D0 contains only ret.
// No caller or identity table proves a semantic owner, so the name keeps the address.
void Rva000EC5D0Noop(void)
{
}
