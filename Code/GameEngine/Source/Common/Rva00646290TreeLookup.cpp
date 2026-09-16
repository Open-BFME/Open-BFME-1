// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00646290Node
{
	char m_pad[0x14];
	void *m_value;
	int m_state;
};

struct Rva00646290Iterator
{
	Rva00646290Node *m_node;
};

class Rva00646290Tree
{
public:
	Rva00646290Iterator find(const int &key);
	Rva00646290Node *m_head;
};

class Rva00646290Owner
{
public:
	void *lookup00646290(int key);
	char m_pad[0x20C];
	Rva00646290Tree m_tree;
};

void *Rva00646290Owner::lookup00646290(int key)
{
	Rva00646290Iterator it = m_tree.find(key);
	if (it.m_node == m_tree.m_head)
		return 0;

	Rva00646290Node *value = (Rva00646290Node *)it.m_node->m_value;
	if (value && value->m_state == 0)
		return 0;
	return value;
}
