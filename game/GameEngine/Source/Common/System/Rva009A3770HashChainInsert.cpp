// ?insert@Rva009A3770HashTable@@QAEPAURva009A3770Node@@PAU2@@Z
extern "C" void *__cdecl memcpy(void *d, const void *s, unsigned int n);

void *__cdecl operator new(unsigned int bytes);		// retail 0x00881F30

struct Rva009A3770Node
{
	unsigned char m_head[0x2c];
	void *m_backSlot;
	Rva009A3770Node *m_next;
};

class Rva009A3770HashTable
{
public:
	Rva009A3770Node *insert(Rva009A3770Node *src);

	Rva009A3770Node *m_buckets[0x493];
	Rva009A3770Node *m_freeList;
};

Rva009A3770Node *Rva009A3770HashTable::insert(Rva009A3770Node *src)
{
	Rva009A3770Node *node = m_freeList;

	if (node)
		m_freeList = node->m_next;
	else
		node = (Rva009A3770Node *)operator new(0x34);

	memcpy(node, src, 0x2c);

	unsigned int idx = ((*(unsigned int *)((char *)src + 8) << 16) + *(unsigned int *)((char *)src + 0xc)) % 0x493;

	Rva009A3770Node **slot = &m_buckets[idx];
	node->m_backSlot = slot;

	Rva009A3770Node *head = *slot;
	node->m_next = head;
	if (head)
		head->m_backSlot = &node->m_next;

	*slot = node;

	return node;
}
