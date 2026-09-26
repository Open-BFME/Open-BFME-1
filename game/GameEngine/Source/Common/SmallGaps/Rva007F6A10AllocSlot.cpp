// ?allocSlot@Rva007F6A10Owner@@QAEPAURva007F6A10Slot@@XZ
struct Rva007F6A10Owner;
struct Rva007F6A10Slot { int m_0; Rva007F6A10Owner* m_owner; void* m_used; char m_pad[0x94 - 12]; };
struct Rva007F6A10Owner { char m_pad[0x58]; Rva007F6A10Slot m_slots[4]; Rva007F6A10Slot* allocSlot(); };
Rva007F6A10Slot* Rva007F6A10Owner::allocSlot()
{
	for (Rva007F6A10Slot* s = m_slots; s < m_slots + 4; ++s) {
		if (s->m_used == 0) {
			s->m_owner = this;
			return s;
		}
	}
	return 0;
}
