// ?clearRva00359330Nodes@@YAXPAURva00359330Record@@@Z
// partial score=0.96 date=2026-09-09
// experiment v4: simplify v3 (drop the hasNode bool, use if(node) directly).
// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class BfmeNodeZ
{
public:
	~BfmeNodeZ();
	BfmeNodeZ *m_next;
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

void clearRva00359330Nodes(Rva00359330Record *record)
{
	if (record->m_nodes)
	{
		do
		{
			BfmeNodeZ *node = *(BfmeNodeZ * volatile *)&record->m_nodes;
			record->m_nodes = record->m_nodes->m_next;
			if (node)
			{
				node->~BfmeNodeZ();
				operator delete(node);
			}
		}
		while (record->m_nodes);
	}
}
