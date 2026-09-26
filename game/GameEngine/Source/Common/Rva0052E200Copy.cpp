// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva0052E200
{
	char m_00;
	BfmeSubB m_04;
	int m_08;

public:
	Rva0052E200(const Rva0052E200 &other);
};

Rva0052E200::Rva0052E200(const Rva0052E200 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
