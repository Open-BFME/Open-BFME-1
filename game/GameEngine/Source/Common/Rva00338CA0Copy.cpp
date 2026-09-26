// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00338CA0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	Rva0036CA00Str m_0C;

public:
	Rva00338CA0(const Rva00338CA0 &other);
};

Rva00338CA0::Rva00338CA0(const Rva00338CA0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
{
}
