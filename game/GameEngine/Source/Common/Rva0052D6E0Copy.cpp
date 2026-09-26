// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva0052D6E0
{
	char m_00;
	BfmeSubA m_04;
	int m_08;

public:
	Rva0052D6E0(const Rva0052D6E0 &other);
};

Rva0052D6E0::Rva0052D6E0(const Rva0052D6E0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
