// Four more: two clamped table reads, a reset through a held thing, and a
// search over eight slots.

class BfmeStateEE
{
public:
	char m_bfmeHead[0x170C];				// +0x0000
	int m_bfmeLevel;					// +0x170C
};

extern BfmeStateEE *g_bfmeStateEE;				// retail 0x012ED5AC

class BfmeRowFB
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeTail[3];					// +0x08
};

class Gen_00752E80
{
public:
	int bfmeFirst(void) const;

private:
	char m_bfmeHead[0x160];					// +0x000
	BfmeRowFB m_bfmeRows[3];				// +0x160
};

// ?bfmeFirst@Gen_00752E80@@QBEHXZ
int Gen_00752E80::bfmeFirst(void) const
{
	int level = g_bfmeStateEE->m_bfmeLevel - 1;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return m_bfmeRows[level].m_bfmeFirst;
}

class Gen_00752EC0
{
public:
	int bfmeSecond(void) const;

private:
	char m_bfmeHead[0x160];					// +0x000
	BfmeRowFB m_bfmeRows[3];				// +0x160
};

// ?bfmeSecond@Gen_00752EC0@@QBEHXZ
int Gen_00752EC0::bfmeSecond(void) const
{
	int level = g_bfmeStateEE->m_bfmeLevel - 1;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return m_bfmeRows[level].m_bfmeSecond;
}

class BfmeThingFB
{
public:
	char m_bfmeHead[0x148];					// +0x000
	bool m_bfmeA;						// +0x148
	bool m_bfmeB;						// +0x149
	bool m_bfmeC;						// +0x14A
	char m_bfmeGap[0x09];					// +0x14B
	int m_bfmeD;						// +0x154
	int m_bfmeE;						// +0x158
};

class Gen_00758630
{
public:
	void bfmeReset(bool flag);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeThingFB *m_bfmeThing;				// +0x0C
};

// ?bfmeReset@Gen_00758630@@QAEX_N@Z
void Gen_00758630::bfmeReset(bool flag)
{
	BfmeThingFB *thing = m_bfmeThing;

	if (thing == 0)
		return;

	thing->m_bfmeA = (flag == false);
	thing->m_bfmeB = false;
	thing->m_bfmeD = 0;
	thing->m_bfmeC = false;
	thing->m_bfmeE = 0;
}

class BfmeSlotFB
{
public:
	void *m_bfmeKey;					// +0x00
	int m_bfmeTail[8];					// +0x04
};

class Gen_00800880
{
public:
	BfmeSlotFB *bfmeFind(void *key);

private:
	char m_bfmeHead[0xD4];					// +0x0D4
	BfmeSlotFB m_bfmeSlots[8];				// +0x0D4
};

// ?bfmeFind@Gen_00800880@@QAEPAVBfmeSlotFB@@PAX@Z
BfmeSlotFB *Gen_00800880::bfmeFind(void *key)
{
	for (int index = 0; index < 8; ++index)
	{
		if (m_bfmeSlots[index].m_bfmeKey == key)
			return &m_bfmeSlots[index];
	}

	return 0;
}
