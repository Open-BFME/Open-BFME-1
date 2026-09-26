// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva00762E80
{
	int m_00;
	int m_04;
	BfmeSubB m_08;
	int m_0c;
	char m_10;

public:
	Rva00762E80(const Rva00762E80 &other);
};

Rva00762E80::Rva00762E80(const Rva00762E80 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
{
}
