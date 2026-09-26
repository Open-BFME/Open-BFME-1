// Finds a keyed 140-byte-record vector and forwards one indexed record to a
// caller-provided consumer.

struct BfmeIndexedMapRecord
{
	char m_data[140];
};

class BfmeIndexedMapVector
{
public:
	int size(void) const { return m_end - m_begin; }
	BfmeIndexedMapRecord &operator[](int index) { return m_begin[index]; }

private:
	BfmeIndexedMapRecord *m_begin;
	BfmeIndexedMapRecord *m_end;
};

struct BfmeIndexedMapNode
{
	char m_prefix[0x14];
	BfmeIndexedMapVector m_records;
};

class BfmeIndexedMapIterator
{
public:
	BfmeIndexedMapNode *m_node;
};

class BfmeIndexedMap
{
public:
	BfmeIndexedMapIterator bfmeFind(const int &key);

private:
	BfmeIndexedMapNode *m_end;

	friend class BfmeIndexedMapOwner;
};

class BfmeIndexedMapConsumer
{
public:
	void bfmeUse(BfmeIndexedMapRecord *record);
};

class BfmeIndexedMapOwner
{
public:
	bool bfmeFindAndUse(int key, int index, BfmeIndexedMapConsumer *consumer);

private:
	char m_prefix[0x10];
	BfmeIndexedMap m_map;
};

// ?bfmeFindAndUse@BfmeIndexedMapOwner@@QAE_NHHPAVBfmeIndexedMapConsumer@@@Z
bool BfmeIndexedMapOwner::bfmeFindAndUse(
	int key,
	int index,
	BfmeIndexedMapConsumer *consumer)
{
	BfmeIndexedMapNode *node;
	BfmeIndexedMap *map = &m_map;
	BfmeIndexedMapIterator iterator = map->bfmeFind(key);
	node = iterator.m_node;
	if (node == map->m_end)
		return false;

	if (index >= node->m_records.size())
		return false;

	consumer->bfmeUse(&node->m_records[index]);
	return true;
}
