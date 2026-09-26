// cl: /O2 /Ob0

class Obj001DCB90
{
public:
	char pad[0x74];
	int m_74;
};

class Rva001DCB90
{
	char pad[8];
	int m_08;

public:
	int eq(const Obj001DCB90 *p) const;
};

int Rva001DCB90::eq(const Obj001DCB90 *p) const
{
	return p->m_74 == m_08;
}
