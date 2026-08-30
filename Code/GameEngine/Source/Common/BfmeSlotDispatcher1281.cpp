class BfmeSlotDispatcher1281
{
public:
	void bfmeApplySlot1281(void *entry, int mode, void *tail);
	void bfmeDispatchSlots1281(int enabled, int mode, void *tail);

private:
	char m_padding000[0x820];
	int m_count;
	void *m_slots[64];
};

void BfmeSlotDispatcher1281::bfmeDispatchSlots1281(int enabled, int mode, void *tail)
{
	int visited = 0;
	for (int index = 0; index < 64; ++index) {
		if (visited == m_count)
			break;
		void *entry = m_slots[index];
		if (entry != 0) {
			switch (mode) {
			case 0:
				if (enabled != 0)
					bfmeApplySlot1281(entry, 0x40, tail);
				break;
			case 1:
				if (enabled != 0)
					bfmeApplySlot1281(entry, 0x80, tail);
				break;
			}
			++visited;
		}
	}
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
