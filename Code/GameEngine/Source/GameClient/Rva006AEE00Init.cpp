// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include <hash_map>
#include <set>

template <typename T> class StringBase
{
public:
	StringBase(const StringBase<T> &other);
	~StringBase();
private:
	void *m_data;
};

extern StringBase<char> g_Va01336E50;

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

	struct Header
	{
		int color;
		void *parent;
		void *left;
		void *right;
	};

	void clearRaw()
	{
		erase(((Header *)header)->parent);
		((Header *)header)->left = header;
		((Header *)header)->parent = 0;
		((Header *)header)->right = header;
		count = 0;
	}

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
	struct BucketVector
	{
		void **m_start;
		void **m_finish;
		void **m_end;

		unsigned int size() const
		{
			return (unsigned int)(m_finish - m_start);
		}

		void *operator[](unsigned int index) const
		{
			return m_start[index];
		}
	};

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
		return m_buckets.size();
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
			next = reinterpret_cast<Node *>(m_buckets[bucket]);
		return next;
	}

	char m_pad00[4];
	BucketVector m_buckets;
	unsigned int m_count;
};

static __forceinline Rva006AEE00Hashtable::Node *
rva006AEE00Next(Rva006AEE00Hashtable::Node *current,
	Rva006AEE00Hashtable *table)
{
	Rva006AEE00Hashtable::Node *next;
	if (current->next)
		return current->next;
	unsigned int bucket = table->bucketNumber(current->value.first);
	unsigned int count = table->bucketCount();
	next = 0;
	while (next == 0 && ++bucket < count)
		next = reinterpret_cast<Rva006AEE00Hashtable::Node *>(
			table->m_buckets[bucket]);
	return next;
}

class Rva006AEE00
{
private:
	void init();

	char m_pad[0x64];
	Rva006AEE00Tree m_tree;
	char m_pad6C[0x630 - 0x6C];
	unsigned char m_ready;
};

void Rva006AEE00::init()
{
	Rva006AEE00ActualSet *actualTree =
		reinterpret_cast<Rva006AEE00ActualSet *>(&m_tree);
	if (!actualTree->empty())
	{
		actualTree->clear();
	}
	Rva006AEE00Tree *tree = &m_tree;

	Rva006AEE00Hashtable::Iterator it =
		reinterpret_cast<Rva006AEE00Hashtable *>(reinterpret_cast<char *>(this) + 0x70)->begin();
	Rva006AEE00Hashtable::Node *current = it.current;
	if (current)
	{
		Rva006AEE00Hashtable *table = it.table;
		while (current)
		{
			Rva006AEE00Info *info = current->value.second;
			if (info->m_lowPassCutoff == 0 && !(info->m_flags & 0x600))
				tree->insert_unique(
					reinterpret_cast<Rva006AEE00Tree::InsertResult *>(&it.current),
					*info->getName());
			current = rva006AEE00Next(current, table);
		}
	}
	m_ready = 1;
}
