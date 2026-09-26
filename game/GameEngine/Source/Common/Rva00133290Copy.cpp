// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00133290
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	char m_10;
	char m_11;

public:
	Rva00133290(const Rva00133290 &other);
};

Rva00133290::Rva00133290(const Rva00133290 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
	, m_11(other.m_11)
{
}
