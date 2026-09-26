// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

class Rva002DFFA0
{
	int m_00;
	BfmeSubB m_04;
	char m_08;

public:
	Rva002DFFA0(const Rva002DFFA0 &other);
};

Rva002DFFA0::Rva002DFFA0(const Rva002DFFA0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
