// ?link@Rva008D29B0Node@@QAEXXZ
// The chain head at 0x013387CC is the global this TU spells Rva008D29B0Head;
// Rva008D29A0Link.cpp defines it as ?g_rva008D29A0, a Rva008D29A0*. Only the
// pointer value moves here, so the defining name is referenced by its own class
// name (forward declared, never defined in this TU).
struct Rva008D29B0Node { int m_0; int m_4; Rva008D29B0Node* m_next; void link(); };
class Rva008D29A0;
extern Rva008D29A0* g_rva008D29A0;
void Rva008D29B0Node::link()
{
	m_next = (Rva008D29B0Node*)g_rva008D29A0;
	g_rva008D29A0 = (Rva008D29A0*)this;
}
