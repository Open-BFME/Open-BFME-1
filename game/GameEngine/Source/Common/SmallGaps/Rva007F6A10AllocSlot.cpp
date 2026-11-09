// ?allocSlot@Rva007F6A10Owner@@QAEPAURva007F6A10Slot@@XZ
struct Rva007F6A10Owner;
struct Rva007F6A10Slot { int m_0; Rva007F6A10Owner* m_owner; void* m_used; char m_pad[0x94 - 12]; };
struct Rva007F6A10Owner { char m_pad[0x58]; Rva007F6A10Slot m_slots[4]; Rva007F6A10Slot* allocSlot(); };
Rva007F6A10Slot* Rva007F6A10Owner::allocSlot()
{
	for (Rva007F6A10Slot* slot = m_slots; slot < m_slots + 4; ++slot) {
		if (slot->m_used == 0) {
			slot->m_owner = this;
			return slot;
		}
	}
	return 0;
}
