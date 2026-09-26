// ?notifyMembers@Rva001563E0Owner@@QAEXHH@Z
struct Rva001563E0Sub { void notify(int a, int b); };
struct Rva001563E0Target { char m_pad[0x20]; Rva001563E0Sub m_sub; };
struct Rva001563E0Payload { char m_pad[0x204]; Rva001563E0Target* m_target; };
struct Rva001563E0Link { Rva001563E0Link* m_next; Rva001563E0Link* m_prev; Rva001563E0Payload* m_payload; };
struct Rva001563E0Owner {
	int m_0;
	Rva001563E0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001563E0Owner::notifyMembers(int a, int b)
{
	for (Rva001563E0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001563E0Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
