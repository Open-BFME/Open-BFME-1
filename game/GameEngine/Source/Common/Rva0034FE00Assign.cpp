// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

struct Rva0034FE00Pod
{
	int a;
	int b;
	int c;
};

class Rva0034FE00
{
	int m_00;
	char m_04;
	int m_08;
	int m_0C;
	Rva0036CA00Str m_10;
	Rva0034FE00Pod m_14;
	int m_20;
	int m_24;

public:
	Rva0034FE00 &operator=(const Rva0034FE00 &other);
};

Rva0034FE00 &Rva0034FE00::operator=(const Rva0034FE00 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_20 = other.m_20;
	m_24 = other.m_24;
	return *this;
}
