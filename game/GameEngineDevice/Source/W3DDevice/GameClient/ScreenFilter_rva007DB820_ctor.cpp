// cl: /O2 /Ob0

// Retail .rdata 0x01128C0C, 28 bytes: the class vftable, seven ILT slots
// (vtable_lookup.py; slot 5 -> matched set 0x007DAE30), no RTTI locator.
void j_00013d3b();
void j_0000a1a5();
void j_0001fdd9();
void j_000184e9();
void j_0003cd1c();
void j_000148c6();
void j_0003fc9c();
extern const void *g_01128C0C[] =
{
	(const void *)&j_00013d3b,
	(const void *)&j_0000a1a5,
	(const void *)&j_0001fdd9,
	(const void *)&j_000184e9,
	(const void *)&j_0003cd1c,
	(const void *)&j_000148c6,
	(const void *)&j_0003fc9c,
};

class Rva007DB820
{
	void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;

public:
	Rva007DB820();
};

Rva007DB820::Rva007DB820()
{
	m_vptr = (void *)g_01128C0C;
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
	m_3C = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
	m_50 = 0;
}
