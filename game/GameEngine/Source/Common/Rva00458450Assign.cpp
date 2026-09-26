// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00458450
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	char m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;

public:
	void operator=(const Rva00458450 &other);
};

void Rva00458450::operator=(const Rva00458450 &other)
{
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_24 = other.m_24;
	m_20 = other.m_20;
	m_28 = other.m_28;
	m_2C = other.m_2C;
}
