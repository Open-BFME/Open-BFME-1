// ?find@Rva0069CBC0Table@@QAEPAURva0069CBC0Node@@PAURva0069CBC0Holder@@@Z
// partial score=0.67 date=2026-09-04
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
struct Rva0069CBC0Key
{
	char m_pad[8];
	unsigned m_id;
};

struct Rva0069CBC0Node
{
	Rva0069CBC0Node *m_next;
	Rva0069CBC0Key *m_key;
};

struct Rva0069CBC0Holder
{
	Rva0069CBC0Key *m_key;
};

class Rva0069CBC0Table
{
public:
	Rva0069CBC0Node *find(Rva0069CBC0Holder *holder);

	char m_pad[4];
	Rva0069CBC0Node **m_buckets;
	Rva0069CBC0Node **m_buckets_end;
};

Rva0069CBC0Node *Rva0069CBC0Table::find(Rva0069CBC0Holder *holder)
{
	Rva0069CBC0Key *key = holder->m_key;
	unsigned id;
	if (key == 0)
		id = 0;
	else
		id = key->m_id;

	Rva0069CBC0Node **end = m_buckets_end;
	unsigned count = (unsigned)(end - m_buckets);
	Rva0069CBC0Node *node = m_buckets[id % count];
	while (node)
	{
		Rva0069CBC0Key *nk = node->m_key;
		bool ok;
		if (nk && key)
			ok = (nk->m_id == key->m_id);
		else
			ok = (nk == key);
		if (ok)
			break;
		node = node->m_next;
	}
	return node;
}
