// cl: /DNDEBUG /MD /EHsc

struct Gen0035D740Node
{
	Gen0035D740Node() : m_a(0), m_index(-1), m_extra(0) {}
	void *m_a;
	int m_index;
	int m_extra;
};

class Gen0035D740Table
{
public:
	int lookup(int key);

private:
	unsigned char m_pad[0xC];
};

class Gen0035D740Elem
{
	unsigned char m_data[0x14];
};

class Gen0035D740
{
public:
	Gen0035D740Node *makeNode(int key);

private:
	unsigned char m_pad[0xC];
	Gen0035D740Table m_table;
	Gen0035D740Elem *m_elems;
};

Gen0035D740Node *Gen0035D740::makeNode(int key)
{
	int index = m_table.lookup(key);
	if (index != -1)
	{
		Gen0035D740Node *node = new Gen0035D740Node;
		node->m_index = index;
		node->m_extra = *(short *)((unsigned char *)m_elems + index * 0x14 + 0xE);
		return node;
	}
	return 0;
}
