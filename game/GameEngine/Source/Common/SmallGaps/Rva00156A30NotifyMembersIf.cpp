// ?notifyMembersIf@Rva00156A30Owner@@QAEXHH@Z
struct Rva00156A30Sub { void notify(int a, int b); };
struct Rva00156A30Target { char m_pad[0x20]; Rva00156A30Sub m_sub; };
struct Rva00156A30Payload { char m_pad[0x204]; Rva00156A30Target* m_target; };
struct Rva00156A30Link { Rva00156A30Link* m_next; Rva00156A30Link* m_prev; Rva00156A30Payload* m_payload; };
struct Rva00156A30Owner {
	int m_0;
	Rva00156A30Link* m_head;
	void notifyMembersIf(int a, int b);
};
void Rva00156A30Owner::notifyMembersIf(int a, int b)
{
	if (!a)
		return;
	for (Rva00156A30Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva00156A30Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
