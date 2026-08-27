// Six more: a delta adjustment, two bounds-checked cell-range operations, a
// hash-bucket lookup, an append to a global table, and another clamped read.

class Gen_0078D130
{
public:
	void bfmeAdjust(int firstX, int firstY, int secondX, int secondY);

private:
	char m_bfmeHead[0xD0];					// +0x000
	int m_bfmeX;						// +0x0D0
	int m_bfmeY;						// +0x0D4
	char m_bfmeGap[5];					// +0x0D8
	bool m_bfmeDirty;					// +0x0DD
};

// ?bfmeAdjust@Gen_0078D130@@QAEXHHHH@Z
void Gen_0078D130::bfmeAdjust(int firstX, int firstY, int secondX, int secondY)
{
	m_bfmeX = m_bfmeX + (secondX - firstX);
	m_bfmeY = m_bfmeY + (secondY - firstY);

	m_bfmeDirty = true;
}

class BfmeCellFC
{
public:
	~BfmeCellFC();

	unsigned char m_bfmeKind;				// +0x00
	unsigned char m_bfmeGap[3];				// +0x01
	int m_bfmeValue;					// +0x04
};

BfmeCellFC::~BfmeCellFC()
{
}

class Gen_008812D0
{
public:
	~Gen_008812D0();
	BfmeCellFC *bfmeAt(int x, int y) const;
	void bfmeGetCellRange(BfmeCellFC **first, BfmeCellFC **last,
		int x1, int x2, int y);

private:
	float m_bfmeOriginX;					// +0x00
	float m_bfmeOriginY;					// +0x04
	unsigned char m_bfmeHead[0x14];			// +0x08
	float m_bfmeCellSizeInv;				// +0x1C
	int m_bfmeWidth;					// +0x20
	int m_bfmeHeight;					// +0x24
	BfmeCellFC *m_bfmeCells;				// +0x28
};

// ??1Gen_008812D0@@QAE@XZ
Gen_008812D0::~Gen_008812D0()
{
	delete[] m_bfmeCells;
}

// ?bfmeAt@Gen_008812D0@@QBEPAVBfmeCellFC@@HH@Z
BfmeCellFC *Gen_008812D0::bfmeAt(int x, int y) const
{
	if (x >= 0 && x < m_bfmeWidth && y >= 0 && y < m_bfmeHeight)
		return &m_bfmeCells[m_bfmeWidth * y + x];

	return 0;
}

// ?bfmeGetCellRange@Gen_008812D0@@QAEXPAPAVBfmeCellFC@@0HHH@Z
void Gen_008812D0::bfmeGetCellRange(BfmeCellFC **first,
	BfmeCellFC **last, int x1, int x2, int y)
{
	if (x2 < 0 || x1 >= m_bfmeWidth || y < 0 || y >= m_bfmeHeight)
	{
		*last = 0;
		*first = 0;
		return;
	}

	BfmeCellFC *row = m_bfmeCells + y * m_bfmeWidth;
	*last = row;
	*first = row;
	if (x1 > 0)
		*first = row + x1;

	*last += x2 < m_bfmeWidth ? x2 + 1 : m_bfmeWidth;
}

class BfmeNodeFC
{
public:
	BfmeNodeFC *m_bfmeNext;					// +0x00
	unsigned int m_bfmeKey;					// +0x04
};

class Gen_00889290
{
public:
	BfmeNodeFC *bfmeFind(unsigned int key) const;

private:
	int m_bfmeHead[6];					// +0x00
	BfmeNodeFC *m_bfmeBuckets[10007];			// +0x18
};

// ?bfmeFind@Gen_00889290@@QBEPAVBfmeNodeFC@@I@Z
BfmeNodeFC *Gen_00889290::bfmeFind(unsigned int key) const
{
	BfmeNodeFC *node = m_bfmeBuckets[key % 10007];

	while (node != 0)
	{
		if (node->m_bfmeKey == key)
			return node;

		node = node->m_bfmeNext;
	}

	return 0;
}

class BfmeTripleDU
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

extern BfmeTripleDU g_bfmeEntriesDU[16];			// retail 0x013378E0
extern int g_bfmeCountDU;					// retail 0x013379A4

// ?bfmeAppend@@YAXHHH@Z
void __cdecl bfmeAppend(int first, int second, int third)
{
	int index = g_bfmeCountDU;

	g_bfmeEntriesDU[index].m_bfmeFirst = first;
	g_bfmeEntriesDU[index].m_bfmeSecond = second;
	g_bfmeEntriesDU[index].m_bfmeThird = third;

	g_bfmeCountDU = index + 1;
}

class BfmeStateEE
{
public:
	char m_bfmeHead[0x170C];				// +0x0000
	int m_bfmeLevel;					// +0x170C
};

extern BfmeStateEE *g_bfmeStateEE;				// retail 0x012ED5AC

class BfmeRowFC
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeThird;					// +0x08
	int m_bfmeTail[2];					// +0x0C
};

class BfmeHolderFC
{
public:
	char m_bfmeHead[0x15C];					// +0x000
	BfmeRowFC m_bfmeRows[3];				// +0x15C
};

class Gen_00752FF0
{
public:
	int bfmeThird(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeHolderFC *m_bfmeHolder;				// +0x04
};

// ?bfmeThird@Gen_00752FF0@@QBEHXZ
int Gen_00752FF0::bfmeThird(void) const
{
	int level = g_bfmeStateEE->m_bfmeLevel - 1;

	BfmeHolderFC *holder = m_bfmeHolder;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return holder->m_bfmeRows[level].m_bfmeThird;
}
