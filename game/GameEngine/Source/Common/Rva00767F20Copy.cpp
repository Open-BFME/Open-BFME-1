// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva00767F20
{
	int m_00;
	int m_04;
	int m_08;
	BfmeSubB m_0c;
	int m_10;

public:
	Rva00767F20(const Rva00767F20 &other);
};

Rva00767F20::Rva00767F20(const Rva00767F20 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
{
}
