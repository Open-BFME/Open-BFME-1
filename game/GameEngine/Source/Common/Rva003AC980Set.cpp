// cl: /O2 /Ob0

struct Rva003AC980Mid
{
	int a, b, c;
};

class Rva003AC980
{
public:
	virtual void dummy();
	int m_04;
	Rva003AC980Mid m_08;
	int m_14, m_18;
	char m_1C;
	Rva003AC980 &operator=(const Rva003AC980 &o);
};

Rva003AC980 &Rva003AC980::operator=(const Rva003AC980 &o)
{
	m_04 = o.m_04;
	m_08 = o.m_08;
	m_14 = o.m_14;
	m_18 = o.m_18;
	m_1C = o.m_1C;
	return *this;
}
