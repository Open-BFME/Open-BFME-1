// cl: /DNDEBUG /MD /Ireference/shims/stlp_nodealloc /Ivendor/stlport
//
// Retail 0x006AEE00: thiscall returning StringBase by hidden pointer.  If the
// ready byte at +0x630 is clear, run init.  Find in the tree at +0x64, maybe
// increment, then copy either the empty string or the payload at node+0x10.

template <typename T> class StringBase
{
	friend class Rva006AEE00;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	void *m_data;
};

extern StringBase<char> g_Va01336E50;

void *rbIncrement(void *node);
void *rbDecrement(void *node);

class Rva006AEE00Tree
{
public:
	void *find(void *key);

	struct InsertResult
	{
		void *iterator;
		bool inserted;
	};

	void insert_unique(InsertResult *result, const StringBase<char> &key);
	void erase(void *root);

	void *header;
	int count;
};

class Rva006AEE00Info
{
public:
	virtual void vfn00();
	virtual const StringBase<char> *getName();

	char m_pad38[0x38 - 4];
	unsigned int m_flags;
	char m_pad84[0x84 - 0x3c];
	unsigned int m_lowPassCutoff;
};

#include "Common/STLTypedefs.h"

struct Rva006AEE00Less
{
	bool operator()(const StringBase<char> &, const StringBase<char> &) const;
};

struct Rva006AEE00Hash
{
	unsigned int operator()(const StringBase<char> &) const;
};

struct Rva006AEE00Equal
{
	bool operator()(const StringBase<char> &, const StringBase<char> &) const;
};

typedef _STL::set<StringBase<char>, Rva006AEE00Less> Rva006AEE00ActualSet;
typedef _STL::hash_map<StringBase<char>, Rva006AEE00Info *,
	Rva006AEE00Hash, Rva006AEE00Equal>
	Rva006AEE00ActualHashtable;

class Rva006AEE00Hashtable
{
public:
	struct Value
	{
		StringBase<char> first;
		Rva006AEE00Info *second;
	};

	struct Node
	{
		Node *next;
		Value value;
	};

	struct Iterator
	{
		Node *current;
		Rva006AEE00Hashtable *table;

		Iterator &operator++()
		{
			Node *next = current->next;
			current = next != 0 ? next : table->skipToNext(current);
			return *this;
		}
	};

	Iterator begin();
	unsigned int bucketCount() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	unsigned int bucketNumber(const StringBase<char> &key) const
	{
		return bucketNumber(key, bucketCount());
	}

	unsigned int bucketNumber(const StringBase<char> &key, unsigned int count) const;

	Node *skipToNext(Node *current)
	{
		unsigned int bucket = bucketNumber(current->value.first);
		unsigned int count;
		count = bucketCount();
		Node *next = 0;
		while (next == 0 && ++bucket < count)
			next = reinterpret_cast<Node *>(m_start[bucket]);
		return next;
	}

	char m_pad00[4];
	void **m_start;
	void **m_finish;
	void **m_end;
	unsigned int m_count;
};

class Rva006AEE00
{
public:
	StringBase<char> get(void *key);
	StringBase<char> getPrev(void *key);

private:
	void init();

	char m_pad[0x64];
	Rva006AEE00Tree m_tree;
	char m_pad6C[0x630 - 0x6C];
	unsigned char m_ready;
};

StringBase<char> Rva006AEE00::get(void *key)
{
	if (!m_ready)
		init();
	void *it = m_tree.find(key);
	if (it != m_tree.header)
		it = rbIncrement(it);
	void *header = m_tree.header;
	if (it == header)
	{
		it = *((void **)header + 2);
		if (it == header)
			return g_Va01336E50;
	}
	return *reinterpret_cast<StringBase<char> *>((char *)it + 0x10);
}

StringBase<char> Rva006AEE00::getPrev(void *key)
{
	if (!m_ready)
		init();
	if (m_tree.count == 0)
		return g_Va01336E50;
	void *it = m_tree.find(key);
	void *header = m_tree.header;
	if (it == *((void **)header + 2))
		it = header;
	it = rbDecrement(it);
	return *reinterpret_cast<StringBase<char> *>((char *)it + 0x10);
}

class Rva006AEE00TreeHeader
{
public:
	int color;
	void *parent;
	void *left;
	void *right;
};

void Rva006AEE00::init()
{
	Rva006AEE00ActualSet *tree =
		reinterpret_cast<Rva006AEE00ActualSet *>(&m_tree);
	if (!tree->empty())
	{
		tree->clear();
	}

	Rva006AEE00ActualHashtable *table =
		reinterpret_cast<Rva006AEE00ActualHashtable *>(reinterpret_cast<char *>(this) + 0x70);
	Rva006AEE00ActualHashtable::iterator it = table->begin();
	while (it._M_cur)
	{
		Rva006AEE00Info *info = it._M_cur->_M_val.second;
		if (info->m_lowPassCutoff == 0 && !(info->m_flags & 0x600))
			tree->insert(*info->getName());
		++it;
	}
	m_ready = 1;
}
