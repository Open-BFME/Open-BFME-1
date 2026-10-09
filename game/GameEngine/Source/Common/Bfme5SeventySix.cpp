// cl: /GX

class Gen_0078D130
{
public:
	void bfmeAdjust(int firstX, int firstY, int secondX, int secondY);

private:
	char m_bfmeHead[0xD0];
	int m_bfmeX;
	int m_bfmeY;
	char m_bfmeGap[5];
	bool m_bfmeDirty;
};

void Gen_0078D130::bfmeAdjust(int firstX, int firstY, int secondX, int secondY)
{
	m_bfmeX = m_bfmeX + (secondX - firstX);
	m_bfmeY = m_bfmeY + (secondY - firstY);
	m_bfmeDirty = true;
}

class BfmeNodeFC
{
public:
	BfmeNodeFC *m_bfmeNext;
	unsigned int m_bfmeKey;
};

class Gen_00889290
{
public:
	BfmeNodeFC *bfmeFind(unsigned int key) const;

private:
	int m_bfmeHead[6];
	BfmeNodeFC *m_bfmeBuckets[10007];
};

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
	int m_bfmeFirst;
	int m_bfmeSecond;
	int m_bfmeThird;
};

// Recorded retail zero-filled table and count at VA 0x013378E0 / 0x013379A4.
BfmeTripleDU g_bfmeEntriesDU[16];
int g_bfmeCountDU;

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
	char m_bfmeHead[0x170C];
	int m_bfmeLevel;
};

// retail 0x012ED5AC is ?TheGameLODManager@@3PAVGameLODManager@@A; this TU
// keeps its own view of the object and casts at the read.
class GameLODManager;
extern GameLODManager *TheGameLODManager;

class BfmeRowFC
{
public:
	int m_bfmeHead[2];
	int m_bfmeThird;
	int m_bfmeTail[2];
};

class BfmeHolderFC
{
public:
	char m_bfmeHead[0x15C];
	BfmeRowFC m_bfmeRows[3];
};

class Gen_00752FF0
{
public:
	int bfmeThird(void) const;

private:
	int m_bfmeHead;
	BfmeHolderFC *m_bfmeHolder;
};

int Gen_00752FF0::bfmeThird(void) const
{
	int level = reinterpret_cast<BfmeStateEE *>(TheGameLODManager)->m_bfmeLevel - 1;
	BfmeHolderFC *holder = m_bfmeHolder;
	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;
	return holder->m_bfmeRows[level].m_bfmeThird;
}
