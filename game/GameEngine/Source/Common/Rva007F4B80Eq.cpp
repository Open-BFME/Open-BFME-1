// cl: /O2 /Ob0

class Obj007F4B80
{
public:
	char pad[8];
	int m_08;
};

class Rva007F4B80
{
	char pad[0x10];
	int m_10;

public:
	int eq(const Obj007F4B80 *p, int, int) const;
};

int Rva007F4B80::eq(const Obj007F4B80 *p, int, int) const
{
	return p->m_08 == m_10;
}
