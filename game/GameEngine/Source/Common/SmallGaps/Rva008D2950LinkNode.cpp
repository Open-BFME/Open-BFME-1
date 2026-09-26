// ?link@Rva008D2950Node@@QAEXXZ
struct Rva008D2950Node { int m_0; int m_4; Rva008D2950Node* m_next; void link(); };
extern Rva008D2950Node* Rva008D2950Head;
void Rva008D2950Node::link()
{
	m_next = Rva008D2950Head;
	Rva008D2950Head = this;
}
