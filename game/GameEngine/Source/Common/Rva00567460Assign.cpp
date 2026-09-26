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

class Rva00567460
{
	int m_00;
	Rva005672C0Map m_04;
	Rva00630D00UStr m_10;

public:
	Rva00567460 &operator=(const Rva00567460 *other);
};

Rva00567460 &Rva00567460::operator=(const Rva00567460 *other)
{
	m_04 = *(other ? &other->m_04 : 0);
	m_10 = *(Rva00630D00UStr *)((char *)other + 0x10);
	return *this;
}
