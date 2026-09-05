// cl: /DNDEBUG /MD /EHsc
//
// Near-twin of Gen0035D740::makeNode (twin 0x0035D740,
// Code/GameEngine/Source/GameLogic/ScriptEngine/Gen0035D740Lookup.cpp): same
// lookup-then-allocate shape, but the table/elems pair sits 0x20 bytes
// further into the object (table at +0x2C, elems at +0x38 instead of +0xC
// and +0x18).  Address-derived identity; only the leading padding differs.

struct Rva0035D800Node
{
	Rva0035D800Node() : m_a(0), m_index(-1), m_extra(0) {}
	void *m_a;
	int m_index;
	int m_extra;
};

class Rva0035D800Table
{
public:
	int lookup(int key);

private:
	unsigned char m_pad[0xC];
};

class Rva0035D800Elem
{
	unsigned char m_data[0x14];
};

class Rva0035D800
{
public:
	Rva0035D800Node *makeNode(int key);

private:
	unsigned char m_pad[0x2C];
	Rva0035D800Table m_table;
	Rva0035D800Elem *m_elems;
};

// @?makeNode@Rva0035D800@@QAEPAURva0035D800Node@@H@Z 0x0035D800
Rva0035D800Node *Rva0035D800::makeNode(int key)
{
	int index = m_table.lookup(key);
	if (index != -1)
	{
		Rva0035D800Node *node = new Rva0035D800Node;
		node->m_index = index;
		node->m_extra = *(short *)((unsigned char *)m_elems + index * 0x14 + 0xE);
		return node;
	}
	return 0;
}
