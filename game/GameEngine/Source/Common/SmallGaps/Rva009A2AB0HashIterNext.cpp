// ?nextNode@Rva009A2AB0Iter@@QAEPAURva009A2AB0Node@@XZ
struct Rva009A2AB0Node { char m_pad[0x30]; Rva009A2AB0Node* m_next; };
struct Rva009A2AB0Iter {
	Rva009A2AB0Node* m_buckets[0x2B7C];
	int m_index;
	Rva009A2AB0Node* m_cur;
	Rva009A2AB0Node* nextNode();
};
Rva009A2AB0Node* Rva009A2AB0Iter::nextNode()
{
	while (!m_cur) {
		int i = m_index + 1;
		if (i == 0x2B7B)
			return 0;
		m_index = i;
		m_cur = m_buckets[i];
	}
	Rva009A2AB0Node* n = m_cur;
	m_cur = n->m_next;
	return n;
}
