// cl: /O2 /Ob0

class Rva00698DD0Base
{
public:
	Rva00698DD0Base &operator=(const Rva00698DD0Base &other);

private:
	char m_pad[0x70];
};

class Rva00698DD0 : public Rva00698DD0Base
{
	int m_70;
	char m_74;

public:
	Rva00698DD0 &operator=(const Rva00698DD0 &other);
};

Rva00698DD0 &Rva00698DD0::operator=(const Rva00698DD0 &other)
{
	Rva00698DD0Base::operator=(other);
	m_70 = other.m_70;
	m_74 = other.m_74;
	return *this;
}
