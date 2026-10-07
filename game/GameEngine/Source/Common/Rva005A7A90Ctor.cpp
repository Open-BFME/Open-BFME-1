// cl: /O2 /Ob0

// Retail .rdata 0x0110D63C, 8 bytes: CommandTranslator's vftable per the
// translateGameMessage row (slot 0), two ILT slots (vtable_lookup.py).
void j_00022183();
void j_0001e501();
void *g_0110D63C[] =
{
	(void *)&j_00022183,
	(void *)&j_0001e501,
};

class Rva005A7A90
{
	void *m_vptr;
	int m_04;
	char m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	char m_2C;

public:
	Rva005A7A90();
};

Rva005A7A90::Rva005A7A90()
{
	m_vptr = g_0110D63C;
	m_04 = 0;
	m_08 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}
