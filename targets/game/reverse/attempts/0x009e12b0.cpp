// ??0Rva009E12B0Table@@QAE@H@Z
// partial score=0.9 date=2026-09-06
extern "C" void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)
struct Rva009E12B0Pair { int m_a; int m_b; Rva009E12B0Pair() : m_a(0), m_b(0) {} };
struct Rva009E12B0Table {
	int m_owner;
	int m_4;
	int m_8;
	int m_table[0x100];
	Rva009E12B0Pair m_pairs[0x100];
	bool m_flag;
	int m_c10;
	short m_c14;
	Rva009E12B0Table(int owner);
};
Rva009E12B0Table::Rva009E12B0Table(int owner)
	: m_owner(owner), m_4(0), m_8(0)
{
	m_flag = false;
	m_c10 = 0;
	memset(m_table, 0, 0x400);
	memset(m_pairs, 0, 0x800);
	m_c14 = 0;
}
