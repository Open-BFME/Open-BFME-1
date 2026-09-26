// cl: /O2 /Ob0

class Rva001B1800
{
	int m_00[16];
	int m_40[16];
	int m_80;
	int m_84;

public:
	Rva001B1800();
};

Rva001B1800::Rva001B1800()
{
	for (unsigned i = 0; i < 16; i++)
	{
		m_40[i] = 0;
		m_00[i] = 0;
	}
	m_84 = 0;
	m_80 = 0;
}
