// vtable_lookup.py places this body at slot 12 in table 0x010C0E00.
// The constructor and destructor evidence ties that table to ProductionUpdate.
// The method name remains unproven, so the source uses an address-derived owner.

struct Rva0029BE60Node
{
	int m_head;
	int m_kind;
	void *m_key;
	int m_pad0c;
	void *m_data;
	unsigned char m_pad14[0x28];
	Rva0029BE60Node *m_next;
};

class Rva0029BE60Predicate
{
public:
	char query(void *key);
};

extern void j_0003e80b();

typedef char (Rva0029BE60Predicate::*Rva0029BE60Query)(void *);

static __forceinline char rva0029BE60Query(Rva0029BE60Predicate *predicate, void *key)
{
	union { void (*raw)(); Rva0029BE60Query member; } fn;
	fn.raw = j_0003e80b;
	return (predicate->*fn.member)(key);
}

class Rva0029BE60
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20(void *data);

	void sweep(Rva0029BE60Predicate *predicate);

	int m_pad04;
	Rva0029BE60Node *m_head;
};

// ?sweep@Rva0029BE60@@QAEXPAVRva0029BE60Predicate@@@Z
void Rva0029BE60::sweep(Rva0029BE60Predicate *predicate)
{
	Rva0029BE60Node *node = m_head;

	while (node != 0)
	{
		if (node->m_kind == 1 && rva0029BE60Query(predicate, node->m_key))
		{
			Rva0029BE60Node *next = node->m_next;

			slot20(node->m_data);

			node = next;
		}
		else
		{
			node = node->m_next;
		}
	}
}
