// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva002DFC30
{
	int m_00;
	BfmeSubA m_04;
	char m_08;

public:
	Rva002DFC30(const Rva002DFC30 &other);
};

Rva002DFC30::Rva002DFC30(const Rva002DFC30 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
