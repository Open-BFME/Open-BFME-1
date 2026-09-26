// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva0073D400
{
	char m_00[0x2429];
	char m_2429;
	Rva0036CA00Str m_242C;
	Rva0036CA00Str m_2430;

public:
	void set(const Rva0036CA00Str &a, const Rva0036CA00Str &b);
};

void Rva0073D400::set(const Rva0036CA00Str &a, const Rva0036CA00Str &b)
{
	m_2429 = 1;
	m_242C = a;
	m_2430 = b;
}
