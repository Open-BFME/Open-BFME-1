// cl: /O2 /Ob0

class Rva0049A100
{
	int m_00;

public:
	Rva0049A100 &set(int *p);
};

Rva0049A100 &Rva0049A100::set(int *p)
{
	int v = *p;
	*p = 0;
	m_00 = v;
	return *this;
}
