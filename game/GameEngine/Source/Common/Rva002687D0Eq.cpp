// cl: /O2 /Ob0

struct Rva002687D0Inner
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva002687D0Sub
{
	Rva002687D0Inner *m_holder;
};

class Rva002687D0
{
public:
	bool eq(int a) const;
};

bool Rva002687D0::eq(int a) const
{
	return ((const Rva002687D0Sub *)((const char *)this - 0x0C))->m_holder->m_08 == a;
}
