// ?syncTimers@Rva0073C120Owner@@QAEXXZ
struct Rva0073C120Owner
{
	char m_pad[0x28];
	float m_time;
	char m_pad2[0x1c8 - 0x2c];
	bool m_running;
	char m_pad3[3];
	float m_current;
	float m_start;
	char m_pad4[0x1dc - 0x1d4];
	bool m_enabled;
	char m_pad5[0x16e8 - 0x1dd];
	int m_seed;
	int m_slots[1];
	char m_pad6[0x22f0 - 0x16f0];
	int m_slotCount;
	char m_pad7[0x2354 - 0x22f4];
	int m_mode;
	void syncTimers();
};

void Rva0073C120Owner::syncTimers()
{
	if (m_enabled) {
		if (m_running) {
			m_current = 0.0f;
		} else {
			m_current = m_start = m_time;
		}
	}
	if (m_mode != 1)
		return;
	if (*(volatile int *)((char *)this + 0x22f0) <= 0)
		return;
	int i = 0;
	do
	{
		m_slots[i] = m_seed;
		++i;
	}
	while (i < m_slotCount);
}
