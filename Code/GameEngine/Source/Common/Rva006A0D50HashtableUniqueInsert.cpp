// cl: /O2 /GR- /EHsc-

// Open-BFME5: unique insertion into a hash table with an eight-byte value.

void *bfmeAllocNode(unsigned int bytes);

struct BfmeHashValue
{
	unsigned int m_bfmeKey;
	int m_bfmeSecond;
};

void bfmeConstructE(BfmeHashValue *slot, const BfmeHashValue *source);

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

class Gen_006A0D50;

struct BfmeInsertResultE
{
	BfmeInsertResultE(BfmeHashNode *node, Gen_006A0D50 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;
	Gen_006A0D50 *m_bfmeTable;
	bool m_bfmeInserted;
};

class Gen_006A0D50
{
public:
	BfmeInsertResultE bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeBucketVector m_bfmeBuckets;
	int m_bfmeCount;
};

BfmeInsertResultE Gen_006A0D50::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	unsigned int index = key % m_bfmeBuckets.size();
	BfmeHashNode *first = m_bfmeBuckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultE(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructE(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBuckets[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultE(created, this, true);
}
