// ?removeNode@Rva0007B6D0Owner@@QAEXPAURva0007B6D0Node@@@Z
struct Rva0007B6D0Node { virtual ~Rva0007B6D0Node(); Rva0007B6D0Node* m_next; };
struct Rva0007B6D0Owner { int m_0; Rva0007B6D0Node* m_head; void removeNode(Rva0007B6D0Node* target); };
void Rva0007B6D0Owner::removeNode(Rva0007B6D0Node* target)
{
	for (Rva0007B6D0Node* n = m_head; n; n = n->m_next) {
		if (n == target) {
			if (n) {
				m_head = n->m_next;
				delete n;
			}
			return;
		}
	}
}
