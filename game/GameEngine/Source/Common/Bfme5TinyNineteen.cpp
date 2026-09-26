// Three more: a push at the head of the owner's list, a snapshot that copies a
// word and a three-word struct, and a search along a global list that hands
// back the node it stopped on.

class BfmeNodeCK
{
public:
	char m_bfmeHead[0x1BC];					// +0x000
	BfmeNodeCK *m_bfmeNext;					// +0x1BC
};

class BfmeOwnerCK
{
public:
	char m_bfmeHead[0xEC];					// +0x00
	BfmeNodeCK *m_bfmeList;					// +0xEC
};

class Gen_0014A540
{
public:
	void bfmePush(BfmeNodeCK *node);

private:
	int m_bfmeHead[5];					// +0x00
	BfmeOwnerCK *m_bfmeOwner;				// +0x14
};

// ?bfmePush@Gen_0014A540@@QAEXPAVBfmeNodeCK@@@Z
void Gen_0014A540::bfmePush(BfmeNodeCK *node)
{
	BfmeOwnerCK *owner = m_bfmeOwner;

	node->m_bfmeNext = owner->m_bfmeList;

	owner->m_bfmeList = node;
}

class BfmeTripleCK
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

class Gen_0016AD50
{
public:
	void bfmeSnapshot(void);

private:
	int m_bfmeHead[8];					// +0x00
	int m_bfmeValue;					// +0x20
	BfmeTripleCK m_bfmeTriple;				// +0x24
	int m_bfmeGap[12];					// +0x30
	int m_bfmeSavedValue;					// +0x60
	BfmeTripleCK m_bfmeSavedTriple;				// +0x64
};

// ?bfmeSnapshot@Gen_0016AD50@@QAEXXZ
void Gen_0016AD50::bfmeSnapshot(void)
{
	m_bfmeSavedValue = m_bfmeValue;

	m_bfmeSavedTriple = m_bfmeTriple;
}

class BfmeEntryCK
{
public:
	int m_bfmeTag;						// +0x00
	BfmeEntryCK *m_bfmeNext;				// +0x04
	int m_bfmeGap[3];					// +0x08
	void *m_bfmeKey;					// +0x14
};

extern BfmeEntryCK *g_bfmeListCK;				// retail 0x012ED584

// ?bfmeFind@@YAPAVBfmeEntryCK@@PAX@Z
BfmeEntryCK * __cdecl bfmeFind(void *key)
{
	BfmeEntryCK *entry = g_bfmeListCK;

	while (entry)
	{
		if (entry->m_bfmeKey == key)
			break;

		entry = entry->m_bfmeNext;
	}

	return entry;
}
