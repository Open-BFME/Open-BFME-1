// cl: /O2 /Ob0

class Rva005672C0Map
{
public:
	Rva005672C0Map &operator=(const Rva005672C0Map &other);

private:
	int m_pad[3];
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva005673A0Vec
{
public:
	Rva005673A0Vec &operator=(const Rva005673A0Vec &other);

private:
	int m_pad[4];
};

class Rva005674A0
{
	int m_00;
	Rva005672C0Map m_04;
	Rva00630D00UStr m_10;
	Rva005673A0Vec m_14;

public:
	Rva005674A0 &operator=(const Rva005674A0 *other);
};

Rva005674A0 &Rva005674A0::operator=(const Rva005674A0 *other)
{
	m_04 = *(other ? &other->m_04 : 0);
	m_10 = *(Rva00630D00UStr *)((char *)other + 0x10);
	m_14 = *(Rva005673A0Vec *)((char *)other + 0x14);
	return *this;
}
