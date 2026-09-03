// ?clearRva00359530Nodes@@YAXPAURva00359530Record@@@Z
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Walk a Record's +0x10 node list: unlink next, then destroy and delete the
// current node. Retail loads the next link before the null-dtor branch.

void __cdecl operator delete(void *);

class BfmeNodeZ
{
public:
	~BfmeNodeZ();
	BfmeNodeZ *m_next;
};

class BfmeE1281
{
public:
	~BfmeE1281();
	BfmeE1281 *m_next;
};

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	void *m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	BfmeNodeZ *m_nodes;
};

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	void *m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	BfmeE1281 *m_nodes;
};

void clearRva00359330Nodes(Rva00359330Record *record)
{
	if (record->m_nodes)
	{
		do
		{
			BfmeNodeZ *node = *(BfmeNodeZ * volatile *)&record->m_nodes;
			record->m_nodes = *reinterpret_cast<BfmeNodeZ **>(node);
			if (node)
			{
				node->~BfmeNodeZ();
				operator delete(node);
			}
		}
		while (record->m_nodes);
	}
}

void clearRva00359530Nodes(Rva00359530Record *record)
{
	if (record->m_nodes)
	{
		do
		{
			BfmeE1281 *node = *(BfmeE1281 * volatile *)&record->m_nodes;
			record->m_nodes = *reinterpret_cast<BfmeE1281 **>(node);
			if (node)
			{
				node->~BfmeE1281();
				operator delete(node);
			}
		}
		while (record->m_nodes);
	}
}
