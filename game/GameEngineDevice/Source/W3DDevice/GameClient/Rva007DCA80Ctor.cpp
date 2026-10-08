// cl: /O2 /Ob0

extern const void *g_01128C5C[];

class Rva007DCA80
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;
	int m_14;
	int m_18;
	char m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;

public:
	Rva007DCA80();
};

Rva007DCA80::Rva007DCA80()
{
	m_00 = (void *)g_01128C5C;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0x3F800000;
	m_18 = 0x0F;
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
	m_54 = 0;
	m_58 = 0;
	m_5C = 0;
}

extern const void *g_01128C5C[7];

void j_00042442(void);
void j_0001c03f(void);
void j_0002ddda(void);
void j_00003f5d(void);
void j_0004a507(void);
void j_0003c731(void);
void j_00004bba(void);

#pragma section(".rdata", read)
extern "C" __declspec(allocate(".rdata")) const void *__identifier("?g_01128C5C@@3PAPBXA")[7] =
{
	(const void *)&j_00042442,
	(const void *)&j_0001c03f,
	(const void *)&j_0002ddda,
	(const void *)&j_00003f5d,
	(const void *)&j_0004a507,
	(const void *)&j_0003c731,
	(const void *)&j_00004bba
};
