// ?link@Rva008D29C0Node@@QAEXXZ
struct Rva008D29C0Node { int m_0; int m_4; Rva008D29C0Node* m_next; void link(); };
// The free list at 0x013387D0 is the defining Rva008D2A10 chain (see
// Rva008D2A10Link.cpp); the pointer is spelled with its defining type so the
// reference resolves to ?g_rva008D2A10@@3PAVRva008D2A10@@A.
class Rva008D2A10;
extern Rva008D2A10* g_rva008D2A10;
void Rva008D29C0Node::link()
{
	m_next = (Rva008D29C0Node*)g_rva008D2A10;
	g_rva008D2A10 = (Rva008D2A10*)this;
}