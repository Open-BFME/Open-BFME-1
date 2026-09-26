// ?clearChain@Rva00102640Owner@@QAEXXZ
struct Rva00102640Node { virtual ~Rva00102640Node(); Rva00102640Node* m_next; };
struct Rva00102640Owner { int m_pad[7]; Rva00102640Node* m_head; void clearChain(); };
void Rva00102640Owner::clearChain()
{
	Rva00102640Node* p = m_head;
	while (p) {
		Rva00102640Node* n = p->m_next;
		delete p;
		p = n;
	}
	m_head = 0;
}
