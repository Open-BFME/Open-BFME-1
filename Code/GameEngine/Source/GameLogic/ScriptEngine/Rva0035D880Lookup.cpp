// cl: /DNDEBUG /MD /EHsc

struct Rva0035D880Node
{
	Rva0035D880Node() : m_a(0), m_index(-1), m_extra(0) {}
	void *m_a;
	int m_index;
	int m_extra;
};

class Rva0035D880Table
{
public:
	int lookup(int key, int extra);

private:
	unsigned char m_pad[0xC];
};

class Rva0035D880
{
public:
	Rva0035D880Node *makeNode(int key, int extra);

private:
	unsigned char m_pad[0x2C];
	Rva0035D880Table m_table;
	Rva0035D880Node *m_elems;
};

// @?makeNode@Rva0035D880@@QAEPAURva0035D880Node@@HH@Z 0x0035D880
Rva0035D880Node *Rva0035D880::makeNode(int key, int extra)
{
	int index = m_table.lookup(key, extra);
	if (index != -1)
	{
		Rva0035D880Node *node = new Rva0035D880Node;
		node->m_index = index;
		node->m_extra = *(short *)((unsigned char *)m_elems + index * 0x14 + 0xE);
		return node;
	}
	return 0;
}
