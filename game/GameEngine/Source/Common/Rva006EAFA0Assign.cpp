// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

struct Rva006EAFA0Pod
{
	int a[10];
};

class Rva006EAFA0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva006EAFA0Pod m_08;
	int m_30;
	int m_34;

public:
	Rva006EAFA0 &operator=(const Rva006EAFA0 &other);
};

Rva006EAFA0 &Rva006EAFA0::operator=(const Rva006EAFA0 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_30 = other.m_30;
	m_34 = other.m_34;
	return *this;
}
