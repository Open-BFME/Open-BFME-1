// cl: /O2 /Ob0

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	int m_pad[3];
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00698DD0Base
{
public:
	Rva00698DD0Base &operator=(const Rva00698DD0Base &other);

private:
	char m_pad[0x70];
};

class Rva000EB2B0 : public ScienceInfoBase
{
	Rva0036CA00Str m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	Rva00698DD0Base m_24;
	Rva00698DD0Base m_94;
	int m_104;
	int m_108;
	int m_10C;
	int m_110;
	char m_114;
	char m_115;
	Rva0036CA00Str m_118;

public:
	Rva000EB2B0 &operator=(const Rva000EB2B0 &other);
};

Rva000EB2B0 &Rva000EB2B0::operator=(const Rva000EB2B0 &other)
{
	ScienceInfoBase::operator=(other);
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_94 = other.m_94;
	m_104 = other.m_104;
	m_108 = other.m_108;
	m_10C = other.m_10C;
	m_110 = other.m_110;
	m_114 = other.m_114;
	m_115 = other.m_115;
	m_118 = other.m_118;
	return *this;
}
