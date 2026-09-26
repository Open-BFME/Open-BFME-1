// cl: /O2 /Ob0

struct Rva006E19E0Vec
{
	int x;
	int y;
	int z;
};

class Rva006E19E0
{
	char pad[0xD4];
	Rva006E19E0Vec m_d4;
	int m_e0;

public:
	void get(Rva006E19E0Vec *a, int *b);
};

void Rva006E19E0::get(Rva006E19E0Vec *a, int *b)
{
	*a = m_d4;
	*b = m_e0;
}
