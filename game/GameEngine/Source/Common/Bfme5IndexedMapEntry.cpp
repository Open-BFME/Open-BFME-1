// Finds a keyed 140-byte-record vector and forwards one indexed record to a
// caller-provided consumer.

// Retail reaches both helpers through the five-byte ILT thunks at 0x00034243
// and 0x0000D4CC, which the ledger owns as ?j_00034243@@YAXXZ and
// ?j_0000d4cc@@YAXXZ (game/gen_small/thunks_025.cpp, thunks_005.cpp).  Both
// call sites keep ECX as the receiver and push every real argument (the find
// returns a 4-byte iterator, so its hidden return pointer is pushed first), so
// they are spelled as thiscall member pointers taken from the thunk symbols:
// that keeps the direct ILT relocation and the ECX-plus-stack-argument shape.
extern void j_00034243();
extern void j_0000d4cc();

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
private:
	BfmeIndexedMapNode *m_end;

	friend class BfmeIndexedMapOwner;
};

class BfmeIndexedMapConsumer
{
public:
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
	// The out pointer is the FIRST member parameter so that MSVC pushes &key
	// first and the return slot second, which is the order retail uses; the
	// reverse order (and a by-value return) both compile but differ by two
	// bytes.
	union { void (*raw)(); void (BfmeIndexedMap::*member)(BfmeIndexedMapIterator *out, const int &key); } findRoute;
	findRoute.raw = j_00034243;
	BfmeIndexedMapIterator iterator;
	(map->*findRoute.member)(&iterator, key);
	node = iterator.m_node;
	if (node == map->m_end)
		return false;

	if (index >= node->m_records.size())
		return false;

	union { void (*raw)(); void (BfmeIndexedMapConsumer::*member)(BfmeIndexedMapRecord *); } useRoute;
	useRoute.raw = j_0000d4cc;
	(consumer->*useRoute.member)(&node->m_records[index]);
	return true;
}
