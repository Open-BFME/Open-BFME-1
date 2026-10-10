// cl: /O2 /Ob0

void j_000300df();
void j_00040d54();

// Retail table VA 0x0110DDFC: the two existing ILT entries.
void *g_Va0110DDFC[2] = {
	reinterpret_cast<void *>(&j_000300df),
	reinterpret_cast<void *>(&j_00040d54)
};

class Rva005B1A00
{
	void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	char m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
	int m_34;
	int m_38;

public:
	Rva005B1A00();
};

Rva005B1A00::Rva005B1A00()
{
	m_vptr = (void *)g_Va0110DDFC;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
}
