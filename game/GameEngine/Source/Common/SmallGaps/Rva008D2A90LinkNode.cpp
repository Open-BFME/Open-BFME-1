// ?link@Rva008D2A90Node@@QAEXXZ
// The chain head at 0x013387D4 is retail's global ?g_rva008D2A80@@3PAVRva008D2A80@@A,
// defined by Rva008D2A80Link.cpp; only the pointer value crosses here.
class Rva008D2A80;
extern Rva008D2A80* g_rva008D2A80;
struct Rva008D2A90Node { int m_0; int m_4; Rva008D2A90Node* m_next; void link(); };
void Rva008D2A90Node::link()
{
	m_next = (Rva008D2A90Node*)g_rva008D2A80;
	g_rva008D2A80 = (Rva008D2A80*)this;
}
