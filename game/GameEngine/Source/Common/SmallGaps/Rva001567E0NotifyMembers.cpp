// ?notifyMembers@Rva001567E0Owner@@QAEXHH@Z
struct Rva001567E0Sub { void notify(int a, int b); };
struct Rva001567E0Target { char m_pad[0x20]; Rva001567E0Sub m_sub; };
struct Rva001567E0Payload { char m_pad[0x204]; Rva001567E0Target* m_target; };
struct Rva001567E0Link { Rva001567E0Link* m_next; Rva001567E0Link* m_prev; Rva001567E0Payload* m_payload; };
struct Rva001567E0Owner {
	int m_0;
	Rva001567E0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001567E0Owner::notifyMembers(int a, int b)
{
	for (Rva001567E0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001567E0Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
