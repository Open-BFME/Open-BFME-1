// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva001DE4F0
{
	BfmeSubA m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;

public:
	Rva001DE4F0(const Rva001DE4F0 &other);
};

Rva001DE4F0::Rva001DE4F0(const Rva001DE4F0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
{
}
