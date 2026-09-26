// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

struct Rva0010CFF0Pod
{
	int a;
	int b;
	int c;
	int d;
};

class Rva0010CFF0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0010CFF0Pod m_0C;
	Rva0036CA00Str m_1C;
	int m_20;
	Rva00630D00UStr m_24;
	int m_28;
	Rva0036CA00Str m_2C;

public:
	Rva0010CFF0 &operator=(const Rva0010CFF0 &other);
};

Rva0010CFF0 &Rva0010CFF0::operator=(const Rva0010CFF0 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	return *this;
}
