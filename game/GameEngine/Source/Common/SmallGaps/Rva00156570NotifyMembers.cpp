// ?notifyMembers@Rva00156570Owner@@QAEXHH@Z
struct Rva00156570Sub { void notify(int a, int b); };
struct Rva00156570Target { char m_pad[0x20]; Rva00156570Sub m_sub; };
struct Rva00156570Payload { char m_pad[0x204]; Rva00156570Target* m_target; };
struct Rva00156570Link { Rva00156570Link* m_next; Rva00156570Link* m_prev; Rva00156570Payload* m_payload; };
struct Rva00156570Owner {
	int m_0;
	Rva00156570Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00156570Owner::notifyMembers(int a, int b)
{
	for (Rva00156570Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00156570Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
