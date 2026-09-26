// ?notifyMembers@Rva001562C0Owner@@QAEXHH@Z
struct Rva001562C0Sub { void notify(int a, int b); };
struct Rva001562C0Target { char m_pad[0x20]; Rva001562C0Sub m_sub; };
struct Rva001562C0Payload { char m_pad[0x204]; Rva001562C0Target* m_target; };
struct Rva001562C0Link { Rva001562C0Link* m_next; Rva001562C0Link* m_prev; Rva001562C0Payload* m_payload; };
struct Rva001562C0Owner {
	int m_0;
	Rva001562C0Link* m_head;
	void notifyMembers(int a, int b);
};
void Rva001562C0Owner::notifyMembers(int a, int b)
{
	for (Rva001562C0Link* n = m_head->m_next; n != m_head; n = n->m_next) {
		Rva001562C0Target* t = n->m_payload->m_target;
		if (t)
			t->m_sub.notify(a, b);
	}
}
