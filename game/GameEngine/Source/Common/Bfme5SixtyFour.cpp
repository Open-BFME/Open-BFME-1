// Two more: a six-word mask and a bit test taken from the argument.

class BfmeSixEL
{
public:
	unsigned int m_bfmeA;					// +0x00
	unsigned int m_bfmeB;					// +0x04
	unsigned int m_bfmeC;					// +0x08
	unsigned int m_bfmeD;					// +0x0C
	unsigned int m_bfmeE;					// +0x10
	unsigned int m_bfmeF;					// +0x14
};

class Gen_000C90A0
{
public:
	void bfmeAnd(const BfmeSixEL *other);

private:
	unsigned int m_bfmeA;					// +0x00
	unsigned int m_bfmeB;					// +0x04
	unsigned int m_bfmeC;					// +0x08
	unsigned int m_bfmeD;					// +0x0C
	unsigned int m_bfmeE;					// +0x10
	unsigned int m_bfmeF;					// +0x14
};

// ?bfmeAnd@Gen_000C90A0@@QAEXPBVBfmeSixEL@@@Z
void Gen_000C90A0::bfmeAnd(const BfmeSixEL *other)
{
	m_bfmeA = m_bfmeA & other->m_bfmeA;
	m_bfmeB = m_bfmeB & other->m_bfmeB;
	m_bfmeC = m_bfmeC & other->m_bfmeC;
	m_bfmeD = m_bfmeD & other->m_bfmeD;
	m_bfmeE = m_bfmeE & other->m_bfmeE;
	m_bfmeF = m_bfmeF & other->m_bfmeF;
}

class BfmeThingEL
{
public:
	int m_bfmeHead[8];					// +0x00
	unsigned int m_bfmeIndex;				// +0x20
};

class Gen_000D2480
{
public:
	bool bfmeHasBit(const BfmeThingEL *thing) const;

private:
	int m_bfmeHead[29];					// +0x00
	unsigned int m_bfmeWords[8];				// +0x74
};

// ?bfmeHasBit@Gen_000D2480@@QBE_NPBVBfmeThingEL@@@Z
bool Gen_000D2480::bfmeHasBit(const BfmeThingEL *thing) const
{
	if (thing == 0)
		return false;

	unsigned int index = thing->m_bfmeIndex;

	return (m_bfmeWords[index >> 5] & (1 << (index & 31))) != 0;
}
