// cl: /O2 /Ob0

struct Rva00257880Inner
{
	char m_lead[0x1D8];
	int m_1d8;
};

struct Rva00257880Sub
{
	Rva00257880Inner *m_holder;
};

class Rva00257880
{
public:
	bool eq(int a) const;
};

bool Rva00257880::eq(int a) const
{
	return a == ((const Rva00257880Sub *)((const char *)this - 0x1C))->m_holder->m_1d8;
}
