// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void *g_Rva00789900Table[];

class Rva00789900Init
{
public:
	Rva00789900Init(unsigned char flag);

	void *m_table;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned char m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
};

Rva00789900Init::Rva00789900Init(unsigned char flag)
{
	m_04 = 0xffffffff;
	m_08 = 0;
	m_table = g_Rva00789900Table;
	m_0c = 0;
	m_10 = 0;
	m_14 = flag;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2c = 0;
}
