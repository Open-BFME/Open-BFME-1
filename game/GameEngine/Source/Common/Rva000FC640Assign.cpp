// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

struct Rva000FC640Pod
{
	int a;
	int b;
	int c;
};

class Rva000FC640
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	Rva000FC640Pod m_10;
	Rva0036CA00Str m_1C;
	char m_20;

public:
	Rva000FC640 &operator=(const Rva000FC640 &other);
};

Rva000FC640 &Rva000FC640::operator=(const Rva000FC640 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	return *this;
}
