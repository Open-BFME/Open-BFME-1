// cl: /O2 /Ob0

class Rva004C1590Base
{
public:
	Rva004C1590Base(const Rva004C1590Base &other);
	virtual void handle();
};

class Rva004C1590 : public Rva004C1590Base
{
	int m_04;
	int m_08;
	int m_0C;

public:
	Rva004C1590(const Rva004C1590 &other);
};

Rva004C1590::Rva004C1590(const Rva004C1590 &other)
	: Rva004C1590Base(other)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
{
}
