// ??0Rva008F92F0Table@@QAE@XZ
#pragma pack(push, 2)
struct Rva008F92F0Entry { unsigned short m_key; int m_value; };
#pragma pack(pop)
struct Rva008F92F0Table {
	int m_count;
	Rva008F92F0Entry m_entries[16];
	int m_extra;
	Rva008F92F0Table();
};
Rva008F92F0Table::Rva008F92F0Table() : m_count(0), m_extra(0)
{
	for (int i = 0; i < 16; ++i) {
		m_entries[i].m_key = 0xffff;
		m_entries[i].m_value = 0;
	}
}
