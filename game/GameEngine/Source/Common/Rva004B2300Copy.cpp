// cl: /O2 /Ob0

class Rva004B2300Base
{
public:
	Rva004B2300Base(const Rva004B2300Base &other);
	virtual void handle();
};

class Rva004B2300 : public Rva004B2300Base
{
	int m_04;
	int m_08;

public:
	Rva004B2300(const Rva004B2300 &other);
};

Rva004B2300::Rva004B2300(const Rva004B2300 &other)
	: Rva004B2300Base(other)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
