// cl: /O2 /Ob0

struct Rva0072EB40Obj
{
	char pad[0x14];
	int m_14;
	char pad2[0x12ED - 0x18];
	char m_12ED;
};

class Rva0072EB40
{
public:
	void set(Rva0072EB40Obj *p);
};

void Rva0072EB40::set(Rva0072EB40Obj *p)
{
	p->m_12ED = 0;
	p->m_14 = 0;
}
