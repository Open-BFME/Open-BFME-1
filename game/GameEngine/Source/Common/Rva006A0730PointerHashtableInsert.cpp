// cl: /O2 /GR- /EHsc-

// Retail 0x006A0730 is an STLport unique insertion over a pointer-valued
// element.  The generated hash_map<int, Gen_t[3]> claim is contradicted by
// the eight-byte node allocation and by the key's null/offset-8 comparison.

// Address-derived cdecl allocator pin; independently matched retail node pool.
void *Rva0082E540NodeAllocate(unsigned int bytes);

struct Rva006A0730Value
{
	int m_0;
	int m_4;
	int m_hash;
};

struct Rva006A0730Node
{
	Rva006A0730Node *m_next;
	Rva006A0730Value *m_value;
};

class Rva006A0730Table;

struct Rva006A0730Iterator
{
	Rva006A0730Iterator(Rva006A0730Node *node, Rva006A0730Table *table)
		: m_node(node), m_table(table) {}

	Rva006A0730Node *m_node;
	Rva006A0730Table *m_table;
};

struct Rva006A0730Result
{
	Rva006A0730Result(Rva006A0730Node *node, Rva006A0730Table *table,
		bool inserted)
		: m_iterator(node, table), m_inserted(inserted) {}

	Rva006A0730Iterator m_iterator;
	bool m_inserted;
};

struct Rva006A0730Buckets
{
	unsigned int size(void) const
	{
		return (unsigned int)(m_finish - m_start);
	}

	Rva006A0730Node *&operator[](unsigned int index)
	{
		return m_start[index];
	}

	Rva006A0730Node **m_start;
	Rva006A0730Node **m_finish;
	Rva006A0730Node **m_end;
};

class Rva006A0730Table
{
public:
	Rva006A0730Result insert(Rva006A0730Value *const &value);

private:
	char m_head[4];
	Rva006A0730Buckets m_buckets;
	unsigned int m_count;
};

Rva006A0730Result Rva006A0730Table::insert(Rva006A0730Value *const &value)
{
	unsigned int hash = value == 0 ? 0 : (unsigned int)value->m_hash;
	unsigned int bucket = hash % m_buckets.size();
	Rva006A0730Node *first = m_buckets[bucket];

	for (Rva006A0730Node *node = first; node; node = node->m_next)
	{
		Rva006A0730Value *stored = node->m_value;
		bool equal;
		if (stored != 0 && value != 0)
			equal = stored->m_hash == value->m_hash;
		else
			equal = stored == value;
		if (equal)
			return Rva006A0730Result(node, this, false);
	}

	Rva006A0730Node *created =
		(Rva006A0730Node *)Rva0082E540NodeAllocate(sizeof(Rva006A0730Node));
	Rva006A0730Value **slot = &created->m_value;
	created->m_next = 0;
	if (slot)
		*slot = value;
	created->m_next = first;
	m_buckets[bucket] = created;
	++m_count;

	return Rva006A0730Result(created, this, true);
}
