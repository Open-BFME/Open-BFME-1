// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva003AD070
{
	int m_00;
	BfmeSubA m_04;
	char m_08;

public:
	Rva003AD070(const Rva003AD070 &other);
};

Rva003AD070::Rva003AD070(const Rva003AD070 &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
{
}
