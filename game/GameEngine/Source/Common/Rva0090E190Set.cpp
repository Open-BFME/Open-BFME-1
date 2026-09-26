// cl: /O2 /Ob0

struct Rva0090E190Inner
{
	char m_unobserved[0x30];
	int m_value;
};

class Rva0090E190
{
	Rva0090E190Inner *m_inner;

public:
	void set(int value);
};

void Rva0090E190::set(int value)
{
	if (m_inner)
		m_inner->m_value = value;
}
