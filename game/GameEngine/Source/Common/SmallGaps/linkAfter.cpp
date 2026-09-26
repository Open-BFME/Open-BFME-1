// ?linkAfter@@YGPAURva008BD200Node@@PAU1@0@Z
struct Rva008BD200Node {
	virtual void attach();
	char m_pad[0x54 - 4];
	Rva008BD200Node* m_prev;
	Rva008BD200Node* m_next;
};
Rva008BD200Node* __stdcall linkAfter(Rva008BD200Node* after, Rva008BD200Node* node)
{
	node->m_next = after->m_next;
	node->m_prev = after;
	node->attach();
	if (node->m_next)
		node->m_next->m_prev = node;
	node->m_prev->m_next = node;
	return node;
}
