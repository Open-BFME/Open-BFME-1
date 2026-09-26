// ?acquireRef@Rva00929940Owner@@QAEPAURva00929940Ref@@HH@Z
struct Rva00929940Ref { int m_0; int m_refs; };
struct Rva00929940Group { int m_0; int m_4; Rva00929940Ref** m_refs; };
struct Rva00929940Owner {
	char m_pad[0xa4];
	Rva00929940Ref* m_direct[12];
	Rva00929940Group* m_groups[1];
	Rva00929940Ref* acquireRef(int index, int slot);
};
Rva00929940Ref* Rva00929940Owner::acquireRef(int index, int slot)
{
	Rva00929940Group* g = m_groups[slot];
	if (g) {
		Rva00929940Ref* r = g->m_refs[index];
		if (r)
			r->m_refs++;
		return g->m_refs[index];
	}
	if (m_direct[slot]) {
		m_direct[slot]->m_refs++;
		return m_direct[slot];
	}
	return 0;
}
