// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva00762ED0
{
	BfmeSubB m_00;
	char m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	char m_20;

public:
	Rva00762ED0(const Rva00762ED0 &other);
};

Rva00762ED0::Rva00762ED0(const Rva00762ED0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1c(other.m_1c)
	, m_20(other.m_20)
{
}
