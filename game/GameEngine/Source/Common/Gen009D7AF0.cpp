// cl: /DNDEBUG /MD /O2

void __cdecl gen009D73D0(void *dest, void *src);

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};
}

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
		static_cast<Owner *>(this)->bfmeResize(m_count + 1);
		unsigned int bucket = Hash()(value.key) % m_buckets.size();
		BfmeHashNode *head = static_cast<BfmeHashNode *>(m_buckets[bucket]);
		BfmeHashNode *node = static_cast<BfmeHashNode *>(_STL::__new_alloc::allocate(sizeof(BfmeHashNode)));
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
