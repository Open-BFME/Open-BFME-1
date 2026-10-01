// Six small accessors: an emptiness test on a self-linked list, two getters
// that fall back on a shared default, and three setters that mark a global
// before storing.
//
// The emptiness test compares the node's own successor against the node, and
// the result of that comparison is what the caller gets back.

class BfmeNodeBG
{
public:
	BfmeNodeBG *m_next;					// +0x00
};

class AIGroup
{
public:
	bool isEmpty(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeNodeBG *m_memberList;					// +0x04
};

// ?isEmpty@AIGroup@@QBE_NXZ
bool AIGroup::isEmpty(void) const
{
	BfmeNodeBG *node = m_memberList;

	return node->m_next == node;
}

class TeamPrototype
{
public:
	int m_bfmeHead[4];					// +0x00
	int m_name;					// +0x10
	int m_bfmeFieldB;					// +0x14
};

class AsciiString
{
public:
	static AsciiString TheEmptyString;
};
#define g_bfmeDefaultBG ((int *)&AsciiString::TheEmptyString)					// retail 0x01336E50

class Team
{
public:
	int *getName(void) const;
	int *bfmeFieldB(void) const;

private:
	int m_bfmeHead;						// +0x00
	TeamPrototype *m_proto;				// +0x04
};

// ?getName@Team@@QBEPAHXZ
int *Team::getName(void) const
{
	TeamPrototype *thing = m_proto;

	if (!thing)
		return g_bfmeDefaultBG;

	return &thing->m_name;
}

// ?bfmeFieldB@Team@@QBEPAHXZ
int *Team::bfmeFieldB(void) const
{
	TeamPrototype *thing = m_proto;

	if (!thing)
		return g_bfmeDefaultBG;

	return &thing->m_bfmeFieldB;
}

extern unsigned int g_Rva00EEF418;
#define g_bfmeDirtyBG g_Rva00EEF418					// retail 0x012EF418

class Gen_0018F210
{
public:
	void setWaterArea(bool value);
	void setRiver(bool value);
	void setRiverStart(int value);

private:
	char m_bfmeHead[0x32];					// +0x00
	bool m_isWaterArea;						// +0x32
	char m_bfmeGap[0x2D];					// +0x33
	bool m_isRiver;						// +0x60
	char m_bfmeGap2[0x13];					// +0x61
	int m_riverStart;						// +0x74
};

// ?setWaterArea@Gen_0018F210@@QAEX_N@Z
void Gen_0018F210::setWaterArea(bool value)
{
	g_bfmeDirtyBG |= 1;

	m_isWaterArea = value;
}

// ?setRiver@Gen_0018F210@@QAEX_N@Z
void Gen_0018F210::setRiver(bool value)
{
	g_bfmeDirtyBG |= 1;

	m_isRiver = value;
}

// ?setRiverStart@Gen_0018F210@@QAEXH@Z
void Gen_0018F210::setRiverStart(int value)
{
	g_bfmeDirtyBG |= 1;

	m_riverStart = value;
}

// The carved retail boundary at 0x000EC5D0 contains only ret.
// No caller or identity table proves a semantic owner, so the name keeps the address.
void Rva000EC5D0Noop(void)
{
}
