// ?notifyMembers@Rva00155890Owner@@QAEXHH@Z
struct Rva00155890Sub { void notify(int a, int b); };
struct Rva00155890Target { char m_pad[0x20]; Rva00155890Sub m_sub; };
struct Rva00155890Payload { char m_pad[0x204]; Rva00155890Target* m_target; };
struct Rva00155890Link { Rva00155890Link* m_next; Rva00155890Link* m_prev; Rva00155890Payload* m_payload; };
struct Rva00155890Owner {
	int m_0;
	Rva00155890Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva00155890Owner::notifyMembers(int a, int b)
{
	for (Rva00155890Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00155890Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
