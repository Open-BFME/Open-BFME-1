// Five more: a float pair comparison, a word replacement over a range, a table
// seeder, a clamped byte read, and a global table setter.

class BfmeVec2FA
{
public:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
};

// ?bfmeSamePoint@@YAHPBVBfmeVec2FA@@0@Z
int __cdecl bfmeSamePoint(const BfmeVec2FA *first, const BfmeVec2FA *second)
{
	if (first->m_bfmeX == second->m_bfmeX && first->m_bfmeY == second->m_bfmeY)
		return 1;

	return 0;
}

// ?bfmeReplaceWords@@YAXPAG0PBG1@Z
void __cdecl bfmeReplaceWords(unsigned short *first, unsigned short *last, const unsigned short *oldValue, const unsigned short *newValue)
{
	while (first != last)
	{
		if (*first == *oldValue)
			*first = *newValue;

		++first;
	}
}

extern int g_bfmeIndexFA;					// retail 0x012D5DC8
extern int g_bfmeStateFA[];					// retail 0x013387E0

// ?bfmeSeed@@YAXH@Z
void __cdecl bfmeSeed(int seed)
{
	int value = seed | 1;

	g_bfmeIndexFA = 0;

	g_bfmeStateFA[0] = value;

	// A walking pointer with its own countdown; an index loop is strength
	// reduced into an address compare instead.
	int *entry = &g_bfmeStateFA[1];

	int count = 623;

	do
	{
		value = value * 0x10DCD;

		*entry = value;

		++entry;
	}
	while (--count != 0);
}

class BfmeStateEE
{
public:
	char m_bfmeHead[0x170C];				// +0x0000
	int m_bfmeLevel;					// +0x170C
};

extern BfmeStateEE *g_bfmeStateEE;				// retail 0x012ED5AC

class BfmeRowFA
{
public:
	unsigned char m_bfmeKind;				// +0x00
	char m_bfmeTail[19];					// +0x01
};

class Gen_00752E40
{
public:
	unsigned char bfmeKind(void) const;

private:
	char m_bfmeHead[0x15C];					// +0x000
	BfmeRowFA m_bfmeRows[3];				// +0x15C
};

// ?bfmeKind@Gen_00752E40@@QBEEXZ
unsigned char Gen_00752E40::bfmeKind(void) const
{
	int level = g_bfmeStateEE->m_bfmeLevel - 1;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return m_bfmeRows[level].m_bfmeKind;
}

class BfmeEntryFA
{
public:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
};

extern int g_bfmeCurrentFA;					// retail 0x012F1400
extern BfmeEntryFA g_bfmeTableFA[];				// retail 0x012B4FC8

// ?bfmeStore@@YAXHHHH@Z
void __cdecl bfmeStore(int first, int second, int third, int index)
{
	if (index == -1)
		index = g_bfmeCurrentFA;

	g_bfmeTableFA[index].m_bfmeA = first;
	g_bfmeTableFA[index].m_bfmeB = second;
	g_bfmeTableFA[index].m_bfmeC = third;
}
