// ?createStats@Rva0090D210Owner@@QAEXXZ
// partial score=0.7 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
void* __cdecl operator new(unsigned int size) throw();
struct Rva0090D210Stats {
	virtual ~Rva0090D210Stats();
	bool m_flag;
	int m_8; int m_c; int m_10; int m_14; int m_18; int m_1c; int m_20;
	int m_24; int m_28; int m_2c; int m_30;
	int m_34; int m_38; int m_3c;
	int m_40;
	int m_44;
	Rva0090D210Stats()
		: m_flag(false), m_8(0), m_c(0), m_10(0), m_14(0), m_18(0), m_1c(0), m_20(0),
		m_24(1), m_28(1), m_2c(1), m_30(1), m_34(0), m_38(0), m_3c(0), m_40(2), m_44(0)
	{
	}
};
void __cdecl Rva0090D210Attach(void* target);
struct Rva0090D210Owner {
	char m_pad[0x14];
	Rva0090D210Stats* m_stats;
	char m_pad2[0x3c - 0x18];
	void* m_target;
	void createStats();
};
void Rva0090D210Owner::createStats()
{
	m_stats = new Rva0090D210Stats;
	Rva0090D210Attach(m_target);
}
