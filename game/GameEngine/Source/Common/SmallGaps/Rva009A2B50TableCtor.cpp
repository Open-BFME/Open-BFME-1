// ??0Rva009A2B50Table@@QAE@XZ
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
struct Rva009A2B50Table {
	int m_slots[0x493];
	int m_count;
	int m_first;
	int m_last;
	Rva009A2B50Table();
	void restartAt9A2BC0();
};
Rva009A2B50Table::Rva009A2B50Table()
{
	m_first = 0;
	m_last = 0;
	memset(m_slots, 0, sizeof(m_slots));
	m_count = 0;
}

void Rva009A2B50Table::restartAt9A2BC0()
{
	int current = m_slots[0];
	m_first = 0;
	m_last = current;
}
