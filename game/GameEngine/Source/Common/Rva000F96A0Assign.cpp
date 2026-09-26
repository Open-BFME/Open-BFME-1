// cl: /O2 /Ob0

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva000F96A0
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;
	Rva00630D00UStr m_14;
	Rva0036CA00Str m_18;

public:
	Rva000F96A0 &operator=(const Rva000F96A0 &other);
};

Rva000F96A0 &Rva000F96A0::operator=(const Rva000F96A0 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	return *this;
}
