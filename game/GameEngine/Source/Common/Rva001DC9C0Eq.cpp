// cl: /O2 /Ob0

class Obj001DC9C0
{
public:
	char pad[0x23C];
	int m_23C;
};

class Rva001DC9C0
{
	char pad[8];
	int m_08;

public:
	int eq(const Obj001DC9C0 *p) const;
};

int Rva001DC9C0::eq(const Obj001DC9C0 *p) const
{
	return p->m_23C == m_08;
}
