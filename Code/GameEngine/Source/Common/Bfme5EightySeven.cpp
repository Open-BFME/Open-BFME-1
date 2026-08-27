// Four more: a flag that only reaches the target when nothing blocks it, a
// pair of setters that share one dirty bit, a search over a list of pointers
// and a grid lookup that checks both axes.

class BfmeTargetHB
{
public:
	int m_bfmeGap;								// +0x00
	unsigned char m_bfmeOn;						// +0x04
};

class Gen_0075B930
{
public:
	void bfmeSetOn(bool on);
private:
	unsigned char m_bfmeGap[0x2e];				// +0x00
	unsigned char m_bfmeOn;						// +0x2e
	unsigned char m_bfmeBlocked;				// +0x2f
	unsigned char m_bfmeGap2[0x3c - 0x30];		// +0x30
	BfmeTargetHB *m_bfmeTarget;					// +0x3c
};

void Gen_0075B930::bfmeSetOn(bool on)
{
	BfmeTargetHB *target = m_bfmeTarget;
	if (target != 0)
	{
		target->m_bfmeOn = (on && !m_bfmeBlocked);
	}
	m_bfmeOn = on;
}

class Gen_0078D170
{
public:
	void bfmeSetPair(int a, int b);
private:
	int m_bfmeGap[52];							// +0x00
	int m_bfmeA;								// +0xd0
	int m_bfmeB;								// +0xd4
	unsigned char m_bfmeGap2[0xdd - 0xd8];		// +0xd8
	unsigned char m_bfmeDirty;					// +0xdd
};

void Gen_0078D170::bfmeSetPair(int a, int b)
{
	if (m_bfmeA != a)
	{
		m_bfmeA = a;
		m_bfmeDirty = 1;
	}
	if (m_bfmeB != b)
	{
		m_bfmeB = b;
		m_bfmeDirty = 1;
	}
}

class BfmeThingHA
{
public:
	int m_bfmeGap[2];							// +0x00
	int m_bfmeA;								// +0x08
	int m_bfmeB;								// +0x0c
};

class Gen_00808E90
{
public:
	BfmeThingHA *bfmeFind(const BfmeThingHA *key) const;
private:
	int m_bfmeGap;								// +0x00
	int m_bfmeCount;							// +0x04
	BfmeThingHA **m_bfmeList;					// +0x08
};

BfmeThingHA *Gen_00808E90::bfmeFind(const BfmeThingHA *key) const
{
	for (int index = 0; index < m_bfmeCount; ++index)
	{
		BfmeThingHA *thing = m_bfmeList[index];
		if (thing != 0 && thing->m_bfmeA == key->m_bfmeA && thing->m_bfmeB == key->m_bfmeB)
			return thing;
	}
	return 0;
}

class BfmeCellHC
{
public:
	int m_bfmeGap;								// +0x00
	int m_bfmeValue;							// +0x04
};

class Gen_00881460
{
public:
	int bfmeValueAt(int x, int y) const;
private:
	int m_bfmeGap[8];							// +0x00
	int m_bfmeWidth;							// +0x20
	int m_bfmeHeight;							// +0x24
	BfmeCellHC *m_bfmeCells;					// +0x28
};

int Gen_00881460::bfmeValueAt(int x, int y) const
{
	if (x < 0 || x >= m_bfmeWidth)
		return 0;
	if (y < 0 || y >= m_bfmeHeight)
		return 0;

	BfmeCellHC *cell = &m_bfmeCells[y * m_bfmeWidth + x];
	if (cell == 0)
		return 0;
	return cell->m_bfmeValue;
}
