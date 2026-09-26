// ?processAll@Rva0021E9C0Owner@@QAEXXZ
// Address-derived reconstruction: bail out unless a flag byte at aux+0x168 is
// set, then walk an intrusive circular list rooted at this->m_sentinel
// (sentinel->m_next chain, empty when the walk returns to the sentinel
// itself), calling the already-named thunk 0x0001E303 once per node with
// (node->m_field8, aux->m_field16c) as thiscall(this, ...) arguments.
struct Rva0021E9C0Node
{
	Rva0021E9C0Node* m_next;
	int m_unused4;
	void* m_field8;
};

struct Rva0021E9C0Aux
{
	unsigned char m_pad[0x168];
	unsigned char m_flag;
	unsigned char m_pad2[3];
	void* m_field16c;
};

extern void j_0001e303();

struct Rva0021E9C0Owner
{
	unsigned char m_pad0[4];
	Rva0021E9C0Aux* m_aux;
	unsigned char m_pad2[0x38 - 8];
	Rva0021E9C0Node* m_sentinel;

	void processAll();
};

void Rva0021E9C0Owner::processAll()
{
	typedef void (Rva0021E9C0Owner::*Fn)(void*, void*);
	union { void (*raw)(); Fn member; } fn;
	fn.raw = j_0001e303;

	Rva0021E9C0Aux* aux = m_aux;
	if (!aux->m_flag)
		return;

	Rva0021E9C0Node* sentinel = m_sentinel;
	Rva0021E9C0Node* node = sentinel->m_next;
	if (node == sentinel)
		return;

	do
	{
		void* a1 = node->m_field8;
		void* a2 = aux->m_field16c;
		(this->*fn.member)(a1, a2);
		node = node->m_next;
	} while (node != m_sentinel);
}
