// ?resetInactive@Rva005C2720Owner@@QAEXXZ
struct Rva005C2720Item { virtual void slot0(); virtual void reset(); char m_pad[0x18]; bool m_active; };
struct Rva005C2720Owner { Rva005C2720Item** m_begin; Rva005C2720Item** m_end; void resetInactive(); };
void Rva005C2720Owner::resetInactive()
{
	for (Rva005C2720Item** it = m_begin; it != m_end; ++it) {
		Rva005C2720Item* item = *it;
		if (!item->m_active)
			item->reset();
	}
}
