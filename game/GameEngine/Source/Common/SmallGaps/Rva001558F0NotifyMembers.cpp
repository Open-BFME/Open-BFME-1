// ?notifyMembers@Rva001558F0Owner@@QAEXHH@Z
struct Rva001558F0Sub { void notify(int a, int b); };
struct Rva001558F0Target { char m_pad[0x20]; Rva001558F0Sub m_sub; };
struct Rva001558F0Payload { char m_pad[0x204]; Rva001558F0Target* m_target; };
struct Rva001558F0Link { Rva001558F0Link* m_next; Rva001558F0Link* m_prev; Rva001558F0Payload* m_payload; };
struct Rva001558F0Owner {
	int m_0;
	Rva001558F0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001558F0Owner::notifyMembers(int a, int b)
{
	for (Rva001558F0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001558F0Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
