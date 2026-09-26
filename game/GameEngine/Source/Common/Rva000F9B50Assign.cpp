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

struct Rva000F9B50Pod
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
};

class Rva000F9B50
{
	Rva0036CA00Str m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	Rva000F9B50Pod m_14;
	int m_2C;
	int m_30;
	int m_34;
	char m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	char m_54;
	Rva00630D00UStr m_58;
	Rva0036CA00Str m_5C;

public:
	Rva000F9B50 &operator=(const Rva000F9B50 &other);
};

Rva000F9B50 &Rva000F9B50::operator=(const Rva000F9B50 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3C = other.m_3C;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_50 = other.m_50;
	m_54 = other.m_54;
	m_58 = other.m_58;
	m_5C = other.m_5C;
	return *this;
}
