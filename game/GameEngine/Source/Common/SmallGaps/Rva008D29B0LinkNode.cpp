// ?link@Rva008D29B0Node@@QAEXXZ
struct Rva008D29B0Node { int m_0; int m_4; Rva008D29B0Node* m_next; void link(); };
extern Rva008D29B0Node* Rva008D29B0Head;
void Rva008D29B0Node::link()
{
	m_next = Rva008D29B0Head;
	Rva008D29B0Head = this;
}
