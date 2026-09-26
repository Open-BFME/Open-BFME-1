// ?resetInactive@Rva005C08B0Owner@@QAEXXZ
struct Rva005C08B0Item { virtual void slot0(); virtual void reset(); char m_pad[0x18]; bool m_active; };
struct Rva005C08B0Owner { Rva005C08B0Item** m_begin; Rva005C08B0Item** m_end; void resetInactive(); };
void Rva005C08B0Owner::resetInactive()
{
	for (Rva005C08B0Item** it = m_begin; it != m_end; ++it) {
		Rva005C08B0Item* item = *it;
		if (!item->m_active)
			item->reset();
	}
}
