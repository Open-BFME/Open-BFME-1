// Three more: three floats picked from one of two blocks, a slot reset, and a
// key match.

class BfmeBlockEP
{
public:
	int m_bfmeHead[3];					// +0x00
	float m_bfmeValue;					// +0x0C
};

class BfmeVec3EP
{
public:
	BfmeVec3EP(void)
	{
	}

	BfmeVec3EP(const BfmeVec3EP &other)
	{
		m_bfmeX = other.m_bfmeX;
		m_bfmeY = other.m_bfmeY;
		m_bfmeZ = other.m_bfmeZ;
	}

	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
};

class Gen_001C1D60
{
public:
	BfmeVec3EP bfmeGetRow(void) const;

private:
	int m_bfmeHead[2];					// +0x000
	BfmeBlockEP m_bfmeFirst[3];				// +0x008
	char m_bfmeGap[0x100];					// +0x038
	BfmeBlockEP m_bfmeSecond[3];				// +0x138
	char m_bfmeTail[0x1C];					// +0x168
	bool m_bfmeUseSecond;					// +0x184
};

// ?bfmeGetRow@Gen_001C1D60@@QBE?AVBfmeVec3EP@@XZ
BfmeVec3EP Gen_001C1D60::bfmeGetRow(void) const
{
	const BfmeBlockEP *block = m_bfmeUseSecond ? m_bfmeSecond : m_bfmeFirst;

	BfmeVec3EP out;

	out.m_bfmeX = block[0].m_bfmeValue;
	out.m_bfmeY = block[1].m_bfmeValue;
	out.m_bfmeZ = block[2].m_bfmeValue;

	return out;
}

class BfmeThingEP
{
public:
	int m_bfmeHead[29];					// +0x00
	void *m_bfmeKey;					// +0x74
};

class BfmeStateEP
{
public:
	int m_bfmeHead;						// +0x00
	int m_bfmeKind;						// +0x04
};

class BfmeHolderEP
{
public:
	int m_bfmeHead[22];					// +0x00
	BfmeStateEP *m_bfmeState;				// +0x58
};

class Gen_0026F630
{
public:
	bool bfmeMatches(const BfmeThingEP *thing) const;

private:
	int m_bfmeHead[12];					// +0x000
	BfmeHolderEP *m_bfmeHolder;				// +0x030
	char m_bfmeGap[0x164];					// +0x034
	void *m_bfmeFirst;					// +0x198
	void *m_bfmeSecond;					// +0x19C
};

// ?bfmeMatches@Gen_0026F630@@QBE_NPBVBfmeThingEP@@@Z
bool Gen_0026F630::bfmeMatches(const BfmeThingEP *thing) const
{
	void *key = thing->m_bfmeKey;

	BfmeStateEP *state = m_bfmeHolder->m_bfmeState;

	// Every refusal shares the one block at the end, so the whole test has to
	// be a single conjunction.
	if (state != 0 && state->m_bfmeKind == 0x1A && (m_bfmeFirst == key || m_bfmeSecond == key))
		return true;

	return false;
}
