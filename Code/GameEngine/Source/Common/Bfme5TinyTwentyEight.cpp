// Six more: three floats returned by value, a guarded three-word store, a pop
// that checks the top first, the same reference assignment emitted twice, and
// a detach.

class BfmeVec3CN
{
public:
	BfmeVec3CN(void)
	{
	}

	BfmeVec3CN(const BfmeVec3CN &other)
	{
		m_bfmeX = other.m_bfmeX;
		m_bfmeY = other.m_bfmeY;
		m_bfmeZ = other.m_bfmeZ;
	}

	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
};

class Gen_001B4A20
{
public:
	BfmeVec3CN bfmeGetScale(void) const;

private:
	int m_bfmeHead[28];					// +0x00
	float m_bfmeScaleX;					// +0x70
	int m_bfmeGapA[3];					// +0x74
	float m_bfmeScaleY;					// +0x80
	int m_bfmeGapB[3];					// +0x84
	float m_bfmeScaleZ;					// +0x90
};

// The three loads reach the stack together because the whole vector comes
// back by value.
// ?bfmeGetScale@Gen_001B4A20@@QBE?AVBfmeVec3CN@@XZ
BfmeVec3CN Gen_001B4A20::bfmeGetScale(void) const
{
	// The named return value lands straight in the caller's slot, so the three
	// loads reach the stack in source order and only the exchange is needed.
	BfmeVec3CN scale;

	scale.m_bfmeX = m_bfmeScaleX;
	scale.m_bfmeY = m_bfmeScaleY;
	scale.m_bfmeZ = m_bfmeScaleZ;

	return scale;
}

class BfmeTripleCV
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

class BfmeTargetCV
{
public:
	int m_bfmeHead[5];					// +0x00
	BfmeTripleCV m_bfmeTriple;				// +0x14
};

class Gen_004583D0
{
public:
	void bfmeSetTriple(const BfmeTripleCV *value);

private:
	int m_bfmeHead;						// +0x00
	BfmeTargetCV *m_bfmeTarget;				// +0x04
};

// ?bfmeSetTriple@Gen_004583D0@@QAEXPBVBfmeTripleCV@@@Z
void Gen_004583D0::bfmeSetTriple(const BfmeTripleCV *value)
{
	BfmeTargetCV *target = m_bfmeTarget;

	if (target)
		target->m_bfmeTriple = *value;
}

class BfmeStackCV
{
public:
	int bfmeBack(void) const
	{
		return m_bfmeTop[-1];
	}

	void bfmePop(void)
	{
		m_bfmeTop -= 1;
	}

	int *m_bfmeTop;						// +0x00
};

class Gen_004674E0
{
public:
	void bfmePop(int value);

private:
	int m_bfmeHead[103];					// +0x000
	BfmeStackCV m_bfmeStack;				// +0x19C
	int m_bfmeGap[1];					// +0x1A0
	bool m_bfmeDirty;					// +0x1A4
};

// ?bfmePop@Gen_004674E0@@QAEXH@Z
void Gen_004674E0::bfmePop(int value)
{
	// The step down happens inside the stack's own method, which keeps it as
	// an add to memory instead of a stored register.
	if (m_bfmeStack.bfmeBack() == value)
	{
		m_bfmeStack.bfmePop();

		m_bfmeDirty = true;
	}
}

class BfmeRefCV
{
public:
	int m_bfmeHead;						// +0x00
	int m_bfmeCount;					// +0x04
};

class BfmeHandleCV
{
public:
	int m_bfmeTag;						// +0x00
	BfmeRefCV *m_bfmeRef;					// +0x04
};

class BfmeOwnerCV
{
public:
	char m_bfmeHead[0x1DC];					// +0x000
	int m_bfmeBack;						// +0x1DC
};

extern int g_bfmeTableCV[];					// retail 0x010F77AC

class Gen_00479A30
{
public:
	void bfmeDetach(void);

private:
	int *m_bfmeTable;					// +0x00
	int m_bfmeValue;					// +0x04
	BfmeOwnerCV *m_bfmeOwner;				// +0x08
};

// ?bfmeDetach@Gen_00479A30@@QAEXXZ
void Gen_00479A30::bfmeDetach(void)
{
	BfmeOwnerCV *owner = m_bfmeOwner;

	m_bfmeTable = g_bfmeTableCV;

	if (owner)
	{
		owner->m_bfmeBack = m_bfmeValue;

		m_bfmeOwner = 0;
	}
}
