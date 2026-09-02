// ?bfmeInsertUnique@Gen_006A0BB0@@QAE?AUBfmeInsertResultD@@PBUBfmeHashValue@@@Z
// partial score=0.9 date=2026-09-02
// cl: /O2 /GR- /EHsc-
// Hashtable unique-insert for a 12-byte node (next + 8-byte pair).

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void bfmeConstructD(void *slot, const void *source);	// retail 0x0002C098

struct BfmeHashValue
{
	unsigned int m_bfmeKey;
	int m_bfmeSecond;
};

struct BfmeHashNode
{
	BfmeHashNode *m_bfmeNext;
	BfmeHashValue m_bfmeValue;
};

class Gen_006A0BB0;

struct BfmeInsertResultD
{
	BfmeInsertResultD(BfmeHashNode *node, Gen_006A0BB0 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;
	Gen_006A0BB0 *m_bfmeTable;
	bool m_bfmeInserted;
};

class Gen_006A0BB0
{
public:
	BfmeInsertResultD bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;
	BfmeHashNode **m_bfmeBucketsFinish;
	char m_bfmeGap[4];
	int m_bfmeCount;
};

BfmeInsertResultD Gen_006A0BB0::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultD(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructD(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultD(created, this, true);
}
