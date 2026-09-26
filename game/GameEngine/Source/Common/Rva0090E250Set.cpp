// cl: /O2 /Ob0

struct Rva0090E250Inner
{
	char m_lead[0x38];
	int m_value;
};

class Rva0090E250
{
	Rva0090E250Inner *m_inner;

public:
	void set(int value);
};

void Rva0090E250::set(int value)
{
	if (m_inner)
		m_inner->m_value = value;
}
