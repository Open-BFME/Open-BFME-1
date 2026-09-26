// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva000EB280
{
	char m_00[0x0C];
	Rva0036CA00Str m_0C;
	int m_10;

public:
	void set(const Rva0036CA00Str &s, int v);
};

void Rva000EB280::set(const Rva0036CA00Str &s, int v)
{
	m_0C = s;
	m_10 = v;
}
