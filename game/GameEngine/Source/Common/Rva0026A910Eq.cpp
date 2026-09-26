// cl: /O2 /Ob0

struct Rva0026A910Inner
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva0026A910Sub
{
	Rva0026A910Inner *m_holder;
};

class Rva0026A910
{
public:
	bool eq(int a) const;
};

bool Rva0026A910::eq(int a) const
{
	return ((const Rva0026A910Sub *)((const char *)this - 0x20))->m_holder->m_08 == a;
}
