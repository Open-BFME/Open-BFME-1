// cl: /O2 /Ob0

class Rva0076F980Mid
{
public:
	Rva0076F980Mid &operator=(const Rva0076F980Mid &other);

private:
	int m_00;
	int m_04;
	int m_08;
};

struct Rva00252B90Triple
{
	int a;
	int b;
	int c;
};

class Rva00252B90
{
	int m_00;
	Rva0076F980Mid m_04;
	int m_10;
	Rva00252B90Triple m_14;
	Rva00252B90Triple m_20;

public:
	Rva00252B90 &operator=(const Rva00252B90 &other);
};

Rva00252B90 &Rva00252B90::operator=(const Rva00252B90 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_20 = other.m_20;
	return *this;
}
