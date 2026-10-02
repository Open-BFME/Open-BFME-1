// ?link@Rva008D2A20Node@@QAEXXZ
struct Rva008D2A20Node { int m_0; int m_4; Rva008D2A20Node* m_next; void link(); };
// Chain head at 0x013387D0; defined in game/GameEngine/Source/Common/Rva008D2A10Link.cpp
class Rva008D2A10;
extern Rva008D2A10* g_rva008D2A10;
void Rva008D2A20Node::link()
{
	m_next = (Rva008D2A20Node*)g_rva008D2A10;
	g_rva008D2A10 = (Rva008D2A10*)this;
}
