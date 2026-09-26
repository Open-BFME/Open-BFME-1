// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva001BDA20
{
	char m_00[0x10];
	Rva0036CA00Str m_10;
	int m_14;

public:
	void set(const Rva0036CA00Str &s);
};

void Rva001BDA20::set(const Rva0036CA00Str &s)
{
	m_10 = s;
	m_14 = 4;
}
