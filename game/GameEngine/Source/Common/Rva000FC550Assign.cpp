// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

struct Rva000FC550Pod
{
	int a;
	int b;
	int c;
};

class Rva000FC550
{
	Rva000FC550Pod m_00;
	Rva0036CA00Str m_0C;

public:
	Rva000FC550 &operator=(const Rva000FC550 &other);
};

Rva000FC550 &Rva000FC550::operator=(const Rva000FC550 &other)
{
	m_00 = other.m_00;
	m_0C = other.m_0C;
	return *this;
}
