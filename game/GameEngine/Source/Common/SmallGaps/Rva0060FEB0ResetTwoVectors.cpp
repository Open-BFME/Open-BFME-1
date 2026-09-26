// ?resetAll@Rva0060FEB0Owner@@QAEXXZ
struct Rva0060FEB0Item { virtual void s0(); virtual void s1(); virtual void s2(); virtual void reset(); };
struct Rva0060FEB0Vec { Rva0060FEB0Item** m_begin; Rva0060FEB0Item** m_end;
	unsigned int size() const { return m_end - m_begin; }
	Rva0060FEB0Item* operator[](unsigned int i) const { return m_begin[i]; } };
struct Rva0060FEB0Owner {
	char m_pad[0x240];
	Rva0060FEB0Vec m_second;
	int m_248;
	Rva0060FEB0Vec m_first;
	void resetAll();
};
void Rva0060FEB0Owner::resetAll()
{
	unsigned int i;
	for (i = 0; i < m_first.size(); ++i)
		m_first[i]->reset();
	for (i = 0; i < m_second.size(); ++i)
		m_second[i]->reset();
}
