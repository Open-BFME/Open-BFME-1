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

struct Rva0057D0C0Pod
{
	int a[10];
};

class Rva0057D0C0
{
	int m_00;
	Rva005672C0Map m_04;
	Rva00630D00UStr m_10;
	Rva0057D0C0Pod m_14;

public:
	Rva0057D0C0 &operator=(const Rva0057D0C0 *other);
};

Rva0057D0C0 &Rva0057D0C0::operator=(const Rva0057D0C0 *other)
{
	m_04 = *(other ? &other->m_04 : 0);
	m_10 = *(Rva00630D00UStr *)((char *)other + 0x10);
	m_14 = *(Rva0057D0C0Pod *)((char *)other + 0x14);
	return *this;
}
