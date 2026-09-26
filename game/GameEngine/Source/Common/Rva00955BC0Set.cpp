// cl: /O2 /Ob0

struct Rva00955BC0Vec
{
	int x;
	int y;
	int z;
};

class Rva00955BC0
{
	char m_pad[0xF4];
	int m_F4;
	int m_F8;
	int m_FC;

public:
	void set(const Rva00955BC0Vec *p);
};

void Rva00955BC0::set(const Rva00955BC0Vec *p)
{
	m_F4 = p->x;
	m_F8 = p->y;
	m_FC = p->z;
}
