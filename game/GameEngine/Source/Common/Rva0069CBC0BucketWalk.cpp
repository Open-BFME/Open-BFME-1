// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The bucket walk at retail 0x0069CBC0, reached as Gen0069CBC0::evaluate.
//
// Three matched self-pair makers call this address through their REL32 and
// spell it ?evaluate@Gen0069CBC0@@QAEPAXPAX@Z, so the name comes from the
// callers rather than from this body.  The argument holds a key pointer, the
// owner holds a bucket vector, and the walk returns the first node whose key
// matches, or a null pointer.  A null key matches only another null key.
// What the key and node types really are is not recovered, so their names
// keep this body's address.

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

struct Rva0069CBC0Buckets
{
	Rva0069CBC0Node **m_start;
	Rva0069CBC0Node **m_finish;

	unsigned size(void) const { return (unsigned)(m_finish - m_start); }
	Rva0069CBC0Node *operator[](unsigned slot) const { return m_start[slot]; }
};

class Gen0069CBC0
{
public:
	void *evaluate(void *argument);

	char m_pad[4];
	Rva0069CBC0Buckets m_buckets;
};

void *Gen0069CBC0::evaluate(void *argument)
{
	Rva0069CBC0Key *key = ((Rva0069CBC0Holder *)argument)->m_key;
	unsigned id;
	if (key == 0)
		id = 0;
	else
		id = key->m_id;

	Rva0069CBC0Node *node = m_buckets[id % m_buckets.size()];
	while (node)
	{
		Rva0069CBC0Key *nodeKey = node->m_key;
		bool same;
		if (nodeKey && key)
			same = (nodeKey->m_id == key->m_id);
		else
			same = (nodeKey == key);
		if (same)
			break;
		node = node->m_next;
	}
	return node;
}
