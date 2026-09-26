// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva009CEA90
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;

public:
	Rva009CEA90(const Rva009CEA90 &other);
};

Rva009CEA90::Rva009CEA90(const Rva009CEA90 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
{
}
