// ?notifyMembers@Rva001565D0Owner@@QAEXHH@Z
struct Rva001565D0Sub { void notify(int a, int b); };
struct Rva001565D0Target { char m_pad[0x20]; Rva001565D0Sub m_sub; };
struct Rva001565D0Payload { char m_pad[0x204]; Rva001565D0Target* m_target; };
struct Rva001565D0Link { Rva001565D0Link* m_next; Rva001565D0Link* m_prev; Rva001565D0Payload* m_payload; };
struct Rva001565D0Owner {
	int m_0;
	Rva001565D0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001565D0Owner::notifyMembers(int a, int b)
{
	for (Rva001565D0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001565D0Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
