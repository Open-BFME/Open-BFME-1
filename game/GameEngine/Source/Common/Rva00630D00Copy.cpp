// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva00630D00
{
	Rva0036CA00Str m_00;
	Rva00630D00UStr m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;

public:
	Rva00630D00(const Rva00630D00 &other);
};

Rva00630D00::Rva00630D00(const Rva00630D00 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1C(other.m_1C)
{
}
