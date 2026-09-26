// ??0Rva009A2A20Table@@QAE@XZ
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
struct Rva009A2A20Table {
	int m_slots[0x2b7b];
	int m_count;
	int m_first;
	int m_last;
	Rva009A2A20Table();
};
Rva009A2A20Table::Rva009A2A20Table()
{
	m_first = 0;
	m_last = 0;
	memset(m_slots, 0, sizeof(m_slots));
	m_count = 0;
}
