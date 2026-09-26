// cl: /O2 /Ob0

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);

private:
	void *m_item;
};

class Rva0028BC20
{
	int m_00;
	int m_04;
	char m_08;
	int m_0c;
	BfmeSubA m_10;
	int m_14;

public:
	Rva0028BC20(const Rva0028BC20 &other);
};

Rva0028BC20::Rva0028BC20(const Rva0028BC20 &other)
	: m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
{
}
