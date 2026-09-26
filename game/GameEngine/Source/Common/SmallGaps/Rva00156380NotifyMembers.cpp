// ?notifyMembers@Rva00156380Owner@@QAEXHH@Z
struct Rva00156380Sub { void notify(int a, int b); };
struct Rva00156380Target { char m_pad[0x20]; Rva00156380Sub m_sub; };
struct Rva00156380Payload { char m_pad[0x204]; Rva00156380Target* m_target; };
struct Rva00156380Link { Rva00156380Link* m_next; Rva00156380Link* m_prev; Rva00156380Payload* m_payload; };
struct Rva00156380Owner {
	int m_0;
	Rva00156380Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00156380Owner::notifyMembers(int a, int b)
{
	for (Rva00156380Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00156380Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
