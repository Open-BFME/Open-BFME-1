// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva0043FC20
{
	BfmeSubB m_00;
	int m_04;
	char m_08;
	int m_0c;

public:
	Rva0043FC20(const Rva0043FC20 &other);
};

Rva0043FC20::Rva0043FC20(const Rva0043FC20 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
{
}
