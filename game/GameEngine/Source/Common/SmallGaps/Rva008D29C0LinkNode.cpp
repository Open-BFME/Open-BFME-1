// ?link@Rva008D29C0Node@@QAEXXZ
struct Rva008D29C0Node { int m_0; int m_4; Rva008D29C0Node* m_next; void link(); };
extern Rva008D29C0Node* Rva008D29C0Head;
void Rva008D29C0Node::link()
{
	m_next = Rva008D29C0Head;
	Rva008D29C0Head = this;
}
