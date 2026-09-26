// ?unlinkAfterQuery@@YGXPAURva008BD760Node@@@Z
// partial score=0.85 date=2026-09-06
struct Rva008BD760Node { char m_pad[0x54]; Rva008BD760Node* m_prev; Rva008BD760Node* m_next; };
void __stdcall Rva008BD760Query(Rva008BD760Node* node, int flag, int* out, Rva008BD760Node** nodeRef);
void __stdcall unlinkAfterQuery(Rva008BD760Node* node)
{
	int out;
	Rva008BD760Query(node, 0, &out, &node);
	if (node->m_prev)
		node->m_prev->m_next = node->m_next;
	if (node->m_next)
		node->m_next->m_prev = node->m_prev;
	node->m_prev = 0;
	node->m_next = 0;
}
