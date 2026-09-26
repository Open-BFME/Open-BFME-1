// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva001DE830
{
	BfmeSubB m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;

public:
	Rva001DE830(const Rva001DE830 &other);
};

Rva001DE830::Rva001DE830(const Rva001DE830 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
{
}
