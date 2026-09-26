// ?markAll@Rva003C7350Owner@@QAEXXZ
struct Rva003C7350Item { char m_pad[0xa8]; bool m_marked; };
struct Rva003C7350Vec { Rva003C7350Item** m_begin; Rva003C7350Item** m_end;
	unsigned int size() const { return m_end - m_begin; }
	Rva003C7350Item* operator[](unsigned int i) const { return m_begin[i]; } };
struct Rva003C7350Holder { char m_pad[0x30]; Rva003C7350Vec m_items; };
struct Rva003C7350Owner { int m_0; Rva003C7350Holder* m_holder; void markAll(); };
void Rva003C7350Owner::markAll()
{
	Rva003C7350Vec& v = m_holder->m_items;
	for (unsigned int i = 0; i < v.size(); ++i)
		v[i]->m_marked = true;
}
