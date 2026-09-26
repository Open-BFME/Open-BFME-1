// cl: /O2 /Ob0

class Rva000CC880
{
	int m_00, m_04, m_08, m_0C, m_10, m_14;

public:
	Rva000CC880 &invert();
};

Rva000CC880 &Rva000CC880::invert()
{
	m_00 = ~m_00;
	m_04 = ~m_04;
	m_08 = ~m_08;
	m_0C = ~m_0C;
	m_10 = ~m_10;
	m_14 = ~m_14;
	return *this;
}
