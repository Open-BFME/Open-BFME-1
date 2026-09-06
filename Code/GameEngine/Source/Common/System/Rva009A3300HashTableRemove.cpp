// Address-derived identity: the complete callers and field layout identify a
// 0x493-bucket collision-data table, but no named retail caller is available.
// cl: /O2 /DNDEBUG /MD /EHsc

struct Rva009A3300Node
{
	char m_pad00[8];
	unsigned int m_key0;
	unsigned int m_key1;
	char m_pad10[0x1c];
	Rva009A3300Node **m_backlink;
	Rva009A3300Node *m_next;
};

class Rva009A3300HashTable
{
public:
	void remove(Rva009A3300Node *entry);

private:
	Rva009A3300Node *m_buckets[0x493];
	Rva009A3300Node *m_freeHead;
	void *m_spare;
	Rva009A3300Node *m_cursor;
};

void Rva009A3300HashTable::remove(Rva009A3300Node *entry)
{
	unsigned int key0 = entry->m_key0;
	unsigned int key1 = entry->m_key1;
	unsigned int hash = (key0 << 16) + key1;
	Rva009A3300Node *node = m_buckets[hash % 0x493];

	while (node != 0 &&
		(node->m_key0 != key0 || node->m_key1 != key1))
		node = node->m_next;
	if (node == 0)
		return;

	Rva009A3300Node *cursor = m_cursor;
	if (cursor == node)
		m_cursor = cursor->m_next;
	if (node->m_next != 0)
		node->m_next->m_backlink = node->m_backlink;
	*node->m_backlink = node->m_next;
	node->m_backlink = 0;
	node->m_next = m_freeHead;
	m_freeHead = node;
}
