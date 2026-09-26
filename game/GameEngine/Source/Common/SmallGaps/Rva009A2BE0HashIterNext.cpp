// ?nextNode@Rva009A2BE0Iter@@QAEPAURva009A2BE0Node@@XZ
struct Rva009A2BE0Node { char m_pad[0x30]; Rva009A2BE0Node* m_next; };
struct Rva009A2BE0Iter {
	Rva009A2BE0Node* m_buckets[0x494];
	int m_index;
	Rva009A2BE0Node* m_cur;
	Rva009A2BE0Node* nextNode();
};
Rva009A2BE0Node* Rva009A2BE0Iter::nextNode()
{
	while (!m_cur) {
		int i = m_index + 1;
		if (i == 0x493)
			return 0;
		m_index = i;
		m_cur = m_buckets[i];
	}
	Rva009A2BE0Node* n = m_cur;
	m_cur = n->m_next;
	return n;
}
