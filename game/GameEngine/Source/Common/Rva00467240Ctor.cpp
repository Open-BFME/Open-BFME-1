// cl: /O2 /Ob0

class Rva00467240
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;

public:
	Rva00467240();
};

Rva00467240::Rva00467240()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	char t = (char)((m_10 & 0xF4) | 4);
	m_0C = -1;
	m_10 = t;
}
