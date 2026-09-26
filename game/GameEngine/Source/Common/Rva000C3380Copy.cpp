// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva000C3380
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	char m_0C;
	int m_10;
	char m_14;
	int m_18;

public:
	Rva000C3380(const Rva000C3380 &other);
};

Rva000C3380::Rva000C3380(const Rva000C3380 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
{
}
