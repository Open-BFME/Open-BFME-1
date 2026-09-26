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

class Rva004E9B70
{
	int m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	Rva00630D00UStr m_14;
	Rva00630D00UStr m_18;

public:
	Rva004E9B70 &operator=(const Rva004E9B70 &other);
};

Rva004E9B70 &Rva004E9B70::operator=(const Rva004E9B70 &other)
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
