// Four more: two indexed reads behind the same pair of guards, a vector
// difference returned by value, and another counted handle.

class BfmeElemCY
{
public:
	int m_bfmeHead[3];					// +0x00
	float m_bfmeRatio;					// +0x0C
	int m_bfmeGap;						// +0x10
	int m_bfmeValue;					// +0x14
	int m_bfmeTail[8];					// +0x18
};

class BfmeVecCY
{
public:
	bool bfmeEmpty(void) const
	{
		return m_bfmeStart == m_bfmeFinish;
	}

	BfmeElemCY &bfmeAt(int index) const
	{
		return m_bfmeStart[index];
	}

	BfmeElemCY *m_bfmeStart;				// +0x00
	BfmeElemCY *m_bfmeFinish;				// +0x04
};

class Gen_0075F090
{
public:
	int bfmeValue(void) const;

private:
	int m_bfmeHead[11];					// +0x00
	BfmeVecCY m_bfmeVector;					// +0x2C
	int m_bfmeGap[6];					// +0x34
	int m_bfmeIndex;					// +0x4C
};

// ?bfmeValue@Gen_0075F090@@QBEHXZ
int Gen_0075F090::bfmeValue(void) const
{
	// Both guards have to fail forward, so the read is the fall-through and
	// the two ones share the block at the end.
	if (!m_bfmeVector.bfmeEmpty() && m_bfmeIndex >= 0)
		return m_bfmeVector.bfmeAt(m_bfmeIndex).m_bfmeValue;

	return 1;
}

class BfmeOwnerCY
{
public:
	int m_bfmeHead[11];					// +0x00
	BfmeVecCY m_bfmeVector;					// +0x2C
};

extern float g_bfmeZeroCY;					// retail 0x01075350

class Gen_0075F3D0
{
public:
	float bfmeRatio(void) const;

private:
	int m_bfmeHead[5];					// +0x00
	BfmeOwnerCY *m_bfmeOwner;				// +0x14
	int m_bfmeGap[4];					// +0x18
	int m_bfmeIndex;					// +0x28
};

// ?bfmeRatio@Gen_0075F3D0@@QBEMXZ
float Gen_0075F3D0::bfmeRatio(void) const
{
	BfmeOwnerCY *owner = m_bfmeOwner;

	if (owner != 0 && m_bfmeIndex >= 0)
		return owner->m_bfmeVector.bfmeAt(m_bfmeIndex).m_bfmeRatio;

	return g_bfmeZeroCY;
}

class BfmeVec2CY
{
public:
	BfmeVec2CY(void)
	{
	}

	BfmeVec2CY(const BfmeVec2CY &other)
	{
		m_bfmeX = other.m_bfmeX;
		m_bfmeY = other.m_bfmeY;
	}

	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
};

// ?bfmeSubtract@@YA?AVBfmeVec2CY@@MMPBV1@@Z
BfmeVec2CY __cdecl bfmeSubtract(float x, float y, const BfmeVec2CY *other)
{
	BfmeVec2CY out;

	out.m_bfmeX = x - other->m_bfmeX;
	out.m_bfmeY = y - other->m_bfmeY;

	return out;
}

class BfmeThingCX
{
public:
	int m_bfmeHead;						// +0x00
	unsigned short m_bfmeRefs;				// +0x04
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	BfmeHandleCX(const BfmeHandleCX &other)
	{
		BfmeThingCX *thing = other.m_bfmeThing;

		m_bfmeThing = thing;

		if (thing)
			++thing->m_bfmeRefs;
	}

	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			--m_bfmeThing->m_bfmeRefs;
	}

	BfmeThingCX *m_bfmeThing;				// +0x00
};

class Gen_007AE6B0
{
public:
	BfmeHandleCX bfmeGet(void) const;

private:
	char m_bfmeHead[0x30];					// +0x00
	BfmeHandleCX m_bfmeHandle;				// +0x30
};

// ?bfmeGet@Gen_007AE6B0@@QBE?AVBfmeHandleCX@@XZ
BfmeHandleCX Gen_007AE6B0::bfmeGet(void) const
{
	return m_bfmeHandle;
}
