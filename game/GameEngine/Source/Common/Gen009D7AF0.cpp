// cl: /DNDEBUG /MD /O2 /D_STLP_USE_STATIC_LIB
// stlport

// The insert's resize callee at 0x009D78B0 is the STLport C-string hashtable
// resize specialization; that mangled name is what the ledger holds for the
// address, so reference it exactly and call it through a member-pointer view
// (it is a __thiscall member, so `this` has to travel in ecx).
extern "C" void __identifier("?resize@?$hashtable@URva009D78B0Value@@PBDURva009D78B0Hash@@URva009D78B0ExtractKey@@U?$equal_to@PBD@_STL@@V?$allocator@URva009D78B0Value@@@5@@_STL@@QAEXI@Z")();

// retail 0x009D73D0; no name pinned at that address reproduces it yet, see the
// ledger row tg_009d73d0 (its object symbol is pinned only at 0x000013C5,
// 0x007850E0 and 0x000267F6).
void __cdecl gen009D73D0(void *dest, void *src);

#include <memory>

struct BfmeHashPair
{
	const char *key;
	void *value;
};

struct BfmeHashNode
{
	BfmeHashNode *next;
	BfmeHashPair pair;
};

class Gen009D76F0;

class BfmeHashBuckets
{
public:
	unsigned int size(void) const
	{
		return static_cast<unsigned int>(m_end - m_begin);
	}

	void *&operator[](unsigned int index)
	{
		return m_begin[index];
	}

	void **m_begin;
	void **m_end;
	void **m_capacity;
};

struct BfmeCStringHash
{
	unsigned int operator()(const char *text) const
	{
		unsigned int hash = 0;
		char ch = *text;
		if (ch != 0)
		{
			do
			{
				hash = hash * 5 + static_cast<signed char>(ch);
				ch = *++text;
			}
			while (ch != 0);
		}
		return hash;
	}
};

template <class Value, class Hash, class Owner>
class BfmeHashTable
{
public:
	__forceinline BfmeHashPair &_M_insert(const BfmeHashPair &value)
	{
		union ResizeView
		{
			void (*cdeclView)(unsigned int);
			void (BfmeHashTable::*thiscallView)(unsigned int);
		} resize;

		resize.cdeclView = (void (*)(unsigned int))__identifier("?resize@?$hashtable@URva009D78B0Value@@PBDURva009D78B0Hash@@URva009D78B0ExtractKey@@U?$equal_to@PBD@_STL@@V?$allocator@URva009D78B0Value@@@5@@_STL@@QAEXI@Z");
		(static_cast<Owner *>(this)->*resize.thiscallView)(m_count + 1);
		unsigned int bucket = Hash()(value.key) % m_buckets.size();
		BfmeHashNode *head = static_cast<BfmeHashNode *>(m_buckets[bucket]);
		// Retail 009D7B3D calls pool helper 0082E540 with a 12-byte node.
		BfmeHashNode *node = static_cast<BfmeHashNode *>(_STL::__node_alloc<true, 0>::allocate(sizeof(BfmeHashNode)));
		node->next = 0;
		gen009D73D0(&node->pair, const_cast<BfmeHashPair *>(&value));
		node->next = head;
		m_buckets[bucket] = node;
		++m_count;
		return node->pair;
	}

protected:
	char m_pad[4];
	BfmeHashBuckets m_buckets;
	unsigned int m_count;
};

class Gen009D76F0 : public BfmeHashTable<BfmeHashPair, BfmeCStringHash, Gen009D76F0>
{
public:
	void bfmeResize(unsigned int newCount);
	BfmeHashPair *bfmeInsert(const BfmeHashPair *value);
};

BfmeHashPair *Gen009D76F0::bfmeInsert(const BfmeHashPair *value)
{
	return &_M_insert(*value);
}
