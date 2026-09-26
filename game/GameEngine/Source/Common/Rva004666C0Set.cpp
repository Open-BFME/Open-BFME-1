// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva004666C0
{
	Rva0036CA00Str m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	unsigned char m_flags;

public:
	void set(int a0, const Rva0036CA00Str &a1, const Rva0036CA00Str &a2, int a3);
};

void Rva004666C0::set(int a0, const Rva0036CA00Str &a1, const Rva0036CA00Str &a2, int a3)
{
	m_00 = a2;
	m_04 = a1;
	m_0C = a0;
	if (m_flags & 2)
		m_flags &= (unsigned char)~2;
	if (m_flags & 1)
		m_flags &= (unsigned char)~1;
	m_08 = a3;
	if (m_flags & 8)
		m_flags &= (unsigned char)~8;
}
