// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva001C0B40
{
	int m_00;
	BfmeSubA m_04;
	int m_08;
	int m_0c;

public:
	Rva001C0B40(const Rva001C0B40 &other);
};

Rva001C0B40::Rva001C0B40(const Rva001C0B40 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
{
}
