// ?notifyMembers@Rva001559B0Owner@@QAEXHH@Z
struct Rva001559B0Sub { void notify(int a, int b); };
struct Rva001559B0Target { char m_pad[0x20]; Rva001559B0Sub m_sub; };
struct Rva001559B0Payload { char m_pad[0x204]; Rva001559B0Target* m_target; };
struct Rva001559B0Link { Rva001559B0Link* m_next; Rva001559B0Link* m_prev; Rva001559B0Payload* m_payload; };
struct Rva001559B0Owner {
	int m_0;
	Rva001559B0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001559B0Owner::notifyMembers(int a, int b)
{
	for (Rva001559B0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001559B0Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
