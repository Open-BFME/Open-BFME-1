// ?link@Rva008D2A90Node@@QAEXXZ
struct Rva008D2A90Node { int m_0; int m_4; Rva008D2A90Node* m_next; void link(); };
extern Rva008D2A90Node* Rva008D2A90Head;
void Rva008D2A90Node::link()
{
	m_next = Rva008D2A90Head;
	Rva008D2A90Head = this;
}
