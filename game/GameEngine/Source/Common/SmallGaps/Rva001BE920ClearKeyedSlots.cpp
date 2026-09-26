// ?clearKeyedSlots@Rva001BE920Owner@@QAEXH@Z
struct Rva001BE920Slot { int m_key; unsigned char m_a; unsigned char m_b; unsigned char m_c; unsigned char m_pad; };
struct Rva001BE920Owner {
	char m_pad[0x2d8];
	Rva001BE920Slot m_slots[13];
	char m_pad2[0x346 - 0x2d8 - 13 * 8];
	signed char m_count;
	void refresh();
	void clearKeyedSlots(int key);
};
void Rva001BE920Owner::clearKeyedSlots(int key)
{
	for (int i = 0; i < m_count; ++i) {
		if (m_slots[i].m_key == key) {
			m_slots[i].m_a = 0;
			m_slots[i].m_b = 0;
			m_slots[i].m_c = 0;
			m_slots[i].m_key = 0;
		}
	}
	refresh();
}
