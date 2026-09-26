// ?notifyMembers@Rva00155950Owner@@QAEXHH@Z
struct Rva00155950Sub { void notify(int a, int b); };
struct Rva00155950Target { char m_pad[0x20]; Rva00155950Sub m_sub; };
struct Rva00155950Payload { char m_pad[0x204]; Rva00155950Target* m_target; };
struct Rva00155950Link { Rva00155950Link* m_next; Rva00155950Link* m_prev; Rva00155950Payload* m_payload; };
struct Rva00155950Owner {
	int m_0;
	Rva00155950Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00155950Owner::notifyMembers(int a, int b)
{
	for (Rva00155950Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00155950Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
