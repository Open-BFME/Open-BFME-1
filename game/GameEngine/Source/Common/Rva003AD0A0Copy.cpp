// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva003AD0A0
{
	int m_00;
	int m_04;
	int m_08;
	BfmeSubA m_0c;
	char m_10;

public:
	Rva003AD0A0(const Rva003AD0A0 &other);
};

Rva003AD0A0::Rva003AD0A0(const Rva003AD0A0 &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
{
}
