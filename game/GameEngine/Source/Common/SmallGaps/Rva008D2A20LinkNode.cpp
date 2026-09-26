// ?link@Rva008D2A20Node@@QAEXXZ
struct Rva008D2A20Node { int m_0; int m_4; Rva008D2A20Node* m_next; void link(); };
extern Rva008D2A20Node* Rva008D2A20Head;
void Rva008D2A20Node::link()
{
	m_next = Rva008D2A20Head;
	Rva008D2A20Head = this;
}
