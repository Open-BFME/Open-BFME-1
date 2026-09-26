// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva000946B0G
{
public:
	void bar(void *);
};

Rva000946B0G *g_rva000946b0;

class Rva00094760
{
	int m_00;
	int m_04;
	Rva0036CA00Str m_08;

public:
	void set(const Rva0036CA00Str &src);
};

void Rva00094760::set(const Rva0036CA00Str &src)
{
	m_08 = src;
	g_rva000946b0->bar(this);
}
