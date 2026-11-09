// ?releaseNode@Rva009A2C30Table@@QAEXPAURva009A2C30Node@@@Z
struct Rva009A2C30Node { char m_pad[0x2c]; Rva009A2C30Node** m_prevLink; Rva009A2C30Node* m_next; };
struct Rva009A2C30Table {
	char m_pad[0x124c];
	Rva009A2C30Node* m_free;
	int m_1250;
	Rva009A2C30Node* m_cur;
	void releaseNode(Rva009A2C30Node* n);
};
void Rva009A2C30Table::releaseNode(Rva009A2C30Node* node)
{
	Rva009A2C30Node* cur = m_cur;
	if (cur == node)
		m_cur = cur->m_next;
	if (node->m_next)
		node->m_next->m_prevLink = node->m_prevLink;
	*node->m_prevLink = node->m_next;
	node->m_prevLink = 0;
	node->m_next = m_free;
	m_free = node;
}
