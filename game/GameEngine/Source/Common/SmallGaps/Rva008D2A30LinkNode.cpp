// ?link@Rva008D2A30Node@@QAEXXZ
struct Rva008D2A30Node { int m_0; int m_4; Rva008D2A30Node* m_next; void link(); };
extern Rva008D2A30Node* Rva008D2A30Head;
void Rva008D2A30Node::link()
{
	m_next = Rva008D2A30Head;
	Rva008D2A30Head = this;
}
