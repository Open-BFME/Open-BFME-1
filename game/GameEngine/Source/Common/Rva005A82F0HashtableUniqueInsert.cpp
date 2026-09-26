// cl: /O2 /GR- /EHsc-

// Open-BFME5: unique insertion into a hash table with an eight-byte value.

void *bfmeAllocNode(unsigned int bytes);

struct BfmeHashValue
{
	unsigned int m_bfmeKey;
	int m_bfmeSecond;
};

void bfmeConstructB(BfmeHashValue *slot, const BfmeHashValue *source);

struct BfmeHashNode
{
	BfmeHashNode *m_bfmeNext;
	BfmeHashValue m_bfmeValue;
};

struct BfmeBucketVector
{
	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	BfmeHashNode *&operator[](unsigned int index)
	{
		return m_start[index];
	}

	BfmeHashNode **m_start;
	BfmeHashNode **m_finish;
	BfmeHashNode **m_endOfStorage;
};

class Gen_005A82F0;

struct BfmeInsertResultB
{
	BfmeInsertResultB(BfmeHashNode *node, Gen_005A82F0 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;
	Gen_005A82F0 *m_bfmeTable;
	bool m_bfmeInserted;
};

class Gen_005A82F0
{
public:
	BfmeInsertResultB bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeBucketVector m_bfmeBuckets;
	int m_bfmeCount;
};

BfmeInsertResultB Gen_005A82F0::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	unsigned int index = key % m_bfmeBuckets.size();
	BfmeHashNode *first = m_bfmeBuckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultB(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructB(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBuckets[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultB(created, this, true);
}
