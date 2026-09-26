// ?notifyMembers@Rva00156320Owner@@QAEXHH@Z
struct Rva00156320Sub { void notify(int a, int b); };
struct Rva00156320Target { char m_pad[0x20]; Rva00156320Sub m_sub; };
struct Rva00156320Payload { char m_pad[0x204]; Rva00156320Target* m_target; };
struct Rva00156320Link { Rva00156320Link* m_next; Rva00156320Link* m_prev; Rva00156320Payload* m_payload; };
struct Rva00156320Owner {
	int m_0;
	Rva00156320Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00156320Owner::notifyMembers(int a, int b)
{
	for (Rva00156320Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00156320Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
