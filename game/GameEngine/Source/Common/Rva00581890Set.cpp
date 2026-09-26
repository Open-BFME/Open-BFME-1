// cl: /O2 /Ob0

class Rva00581890
{
	char m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;

public:
	Rva00581890 &set(char a);
};

Rva00581890 &Rva00581890::set(char a)
{
	m_00 = a;
	m_04 = -1;
	m_08 = -1;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	return *this;
}
