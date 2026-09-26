// cl: /O2 /Ob0

struct Rva0033D5C0Pair
{
	int a;
	int *b;
};

class Rva0033D5C0
{
	char m_pad[0x9C];
	int m_9C;

public:
	void set(Rva0033D5C0Pair *out);
};

void Rva0033D5C0::set(Rva0033D5C0Pair *out)
{
	out->a = 0;
	out->b = &m_9C;
}
