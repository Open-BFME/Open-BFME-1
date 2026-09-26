// cl: /O2 /Ob0

struct Rva0033D5A0Pair
{
	int a;
	int *b;
};

class Rva0033D5A0
{
	int m_00;
	int m_04;
	int m_08;

public:
	void set(Rva0033D5A0Pair *out);
};

void Rva0033D5A0::set(Rva0033D5A0Pair *out)
{
	out->a = 0;
	out->b = &m_08;
}
